/**************** THIS IS A REFERENCE IMPLEMENTATION!! ****************
 * window_be_xlib.c: low-level window system backend (X11/Xlib)
 * (c)2004-2009,2011-2015 Seiji Nishimura
 * $Id: window_be_xlib.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 **************** THIS IS A REFERENCE IMPLEMENTATION!! ****************/

#define __WINDOW_BE_INTERNAL__

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#ifdef USE_THREADED_UPDATE
#include <time.h>
#include <pthread.h>
#endif

typedef struct window_be_t {
    Window  base_window,
	    main_window;
    Pixmap       pixmap;
    XImage       ximage;
    GC               gc;
#ifdef USE_THREADED_UPDATE
    pthread_t    thread;
    volatile int arg[4];	/* to specify a rectangle region: (x,y) and (width,height). */
#endif
} *window_be_t;

#include "window_be.h"

/* configuration for shared pixel data */
#undef  USE_SHARED_PIXEL_DATA
#if SIZEOF_PIXEL_T == 4 && !defined(USE_THREADED_UPDATE)
#define USE_SHARED_PIXEL_DATA	1
#endif

/* error codes */
#define ERR_UNKOWN		0	/* unknown error                        */
#define ERR_SYSTEM		1	/* system  error                        */
#define ERR_OPEN_DISPLAY	2	/* error in XOpenDisplay   call         */
#define ERR_VISUAL_CLASS	3	/* cannot find appropriate visual class */
#define ERR_THREAD_INIT		4	/* error in XInitThreads   call         */
#define ERR_THREAD_CREATE	5	/* error in pthread_create call         */
#define ERR_THREAD_JOIN		6	/* error in pthread_join   call         */

/* client message codes */
#define CM_PROTOCOLS		0	/* WM_PROTOCOLS */
#define CM_DELETE_WINDOW	1	/* WM_DELETE_WINDOW  */
#define CM_TABLE_SIZE		2	/* atom[] table size */

/* environment variable codes */
#define EV_RES_NAME		0	/* LIBPIXMAP_X11_RES_NAME           */
#define EV_RES_CLASS		1	/* LIBPIXMAP_X11_RES_CLASS          */
#define EV_RESIZABLE_WINDOW	2	/* LIBPIXMAP_X11_RESIZABLE_WINDOW   */
#define EV_ASYNC		3	/* LIBPIXMAP_X11_ASYNC              */
#define EV_DONT_DELETE_WINDOW	4	/* LIBPIXMAP_X11_DONT_DELETE_WINDOW */
#define EV_TABLE_SIZE		5	/* env[] table size                 */

/* macro functions -----------------------------------------------------*/
#define TABLE_SIZE(tbl)	(sizeof(tbl)/sizeof(tbl[0]))
#define MALLOC(n,t)	((t *)malloc((n)*sizeof(t)))
#define MIN(x,y)	(((x)<(y))?(x):(y))

/* global variables ----------------------------------------------------*/
static char    **env    = NULL;
#ifdef PROCEED_CLIENT_MESSAGE
static Atom    *atom    = NULL;
#endif
static Display *display = NULL;
static Visual  *visual  = NULL;
static Window root_window;
static Colormap  colormap;
static int  depth, screen;

/* internal functions --------------------------------------------------*/
static void  _window_be_init               (void);
static void  _window_be_fin                (void);
static void  _window_be_ximage_init        (XImage *, pixmap_t *);
static void  _window_be_ximage_update      (XImage *, pixmap_t *, int, int, int, int);
static void  _window_be_mask_info          (unsigned long, int *, int *);
static Bool  _window_be_event_predicate    (Display *, XEvent *, XPointer);
static void  _window_be_event_input        (window_input_t *, XEvent *);
static int   _window_be_event_keycode      (KeySym, char *);
static void  _window_be_error              (const char *, const int);
#ifdef USE_THREADED_UPDATE
static int   _window_be_dsleep             (double);
static void *_window_be_update_image_slave (void *);
#endif
#ifdef DEBUG
static void  _window_be_default_visual_info(void);
static void  _window_be_event_info         (XEvent *, const char *);
#endif

/*======================================================================*/
window_be_t _window_be_open(int width, int height, const char *window_name)
{				/* open a graphics window.              */
    window_be_t be;
    XClassHint class_hint;
    XSetWindowAttributes xattr;
    const unsigned long  xattr_mask = 
	CWEventMask | CWColormap | CWBackPixel | CWOverrideRedirect;

    assert(width > 0 && height > 0);
    assert(window_name != NULL);

    if (display == NULL)	/* 1st call: initialization is required. */
	_window_be_init();

    if ((be = MALLOC(1, struct window_be_t)) == NULL)
	_window_be_error(__func__, ERR_SYSTEM);

#ifdef USE_THREADED_UPDATE
    XLockDisplay  (display);
#endif

    /* create window and set up the attributes. */
    xattr.event_mask        =      KeyPressMask | ButtonPressMask | \
			      ButtonReleaseMask | ButtonMotionMask;
#ifdef  DETECT_POINTER_MOTION_NOTIFY
    xattr.event_mask       |= PointerMotionMask;
#endif
    xattr.colormap          = colormap;
    xattr.background_pixel  = WhitePixel(display, screen);
    xattr.override_redirect = False;
    be->base_window         =
	XCreateWindow(display,      root_window, 0, 0, width, height, 0,
		      depth, InputOutput, visual, xattr_mask, &xattr);
    xattr.event_mask        = NoEventMask;
    xattr.override_redirect = True;
    be->main_window         =
	XCreateWindow(display, be->base_window,  0, 0, width, height, 0,
		      depth, InputOutput, visual, xattr_mask, &xattr);

    /* create background pixmap and GC. */
    be->pixmap = XCreatePixmap(display, be->main_window, width, height, depth);
    XSetWindowBackgroundPixmap(display, be->main_window, be->pixmap);
    be->gc     = XCreateGC    (display, be->pixmap, 0, NULL);
    XSetGraphicsExposures     (display, be->gc, False);

    /* resource name */
    class_hint.res_name  = env[EV_RES_NAME ];
    class_hint.res_class = env[EV_RES_CLASS];

    if (env[EV_RESIZABLE_WINDOW] != NULL) {	/* environment variable LIBPIXMAP_X11_RESIZABLE_WINDOW is defined. */
	XStoreName   (display, be->base_window, window_name);
	XSetIconName (display, be->base_window, window_name);
	if (class_hint.res_name  != NULL &&
	    class_hint.res_class != NULL)
	    XSetClassHint(display, be->base_window, &class_hint);
    } else {
	XClassHint *ch = NULL;
	XSizeHints  size_hint;
	XTextProperty   wname;
	/* window size */
	size_hint.flags  = PSize | PMinSize | PMaxSize;
	size_hint.width  = size_hint.min_width  = size_hint.max_width  = width ;
	size_hint.height = size_hint.min_height = size_hint.max_height = height;
	/* window name */
	wname.value    = (unsigned char *) window_name;
	wname.encoding = XA_STRING;
	wname.format   = 8;
	wname.nitems   = strlen(window_name);
	if (class_hint.res_name  != NULL &&
	    class_hint.res_class != NULL)
	    ch = &class_hint;
	/* set up hints for window manager. */
	XSetWMProperties(display, be->base_window, &wname, &wname,
			 NULL, 0, &size_hint, NULL, ch);
    }

#ifdef PROCEED_CLIENT_MESSAGE
    /* register client messages. */
    XSetWMProtocols(display, be->base_window, atom, CM_TABLE_SIZE);
#endif

    /* clear and map window. */
    XSetForeground(display, be->gc, BlackPixel(display, screen));
    XFillRectangle(display, be->pixmap, be->gc, 0, 0, width, height);
    XClearWindow  (display, be->main_window);
    XClearWindow  (display, be->base_window);
    XMapWindow    (display, be->main_window);
    XMapWindow    (display, be->base_window);

#ifdef USE_THREADED_UPDATE
    be->thread = pthread_self();
    XUnlockDisplay(display);
#endif

    /* initialize XImage. */
    memset(&be->ximage, 0x00, sizeof(XImage));

    return be;
}

/*======================================================================*/
void _window_be_close(window_be_t be)
{				/* close a graphics window.             */
#ifdef USE_THREADED_UPDATE
    pthread_t my_thread;
#endif

    assert(display != NULL);
    assert(be      != NULL);

#ifdef USE_THREADED_UPDATE
    if(!pthread_equal(my_thread = pthread_self(), be->thread)) {
	if (pthread_join(be->thread, NULL))	/* failed thread termination. */
	    _window_be_error(__func__, ERR_THREAD_JOIN);
	be->thread = my_thread;
    }
#endif

#ifdef USE_THREADED_UPDATE
    XLockDisplay  (display);
#endif
    XUnmapWindow  (display, be->base_window);
    XUnmapWindow  (display, be->main_window);
    XDestroyWindow(display, be->main_window);
    XDestroyWindow(display, be->base_window);
    XFreePixmap   (display, be->pixmap);
    XFreeGC       (display, be->gc);
#ifdef USE_THREADED_UPDATE
    XUnlockDisplay(display);
#endif

#ifdef USE_SHARED_PIXEL_DATA
    if (visual->red_mask   != 0x00ff0000 ||
	visual->green_mask != 0x0000ff00 ||
	visual->blue_mask  != 0x000000ff)
#endif
    free(be->ximage.data);

    free(be);

    return;
}

/*======================================================================*/
void _window_be_update_image(window_be_t be, pixmap_t *pixmap,
			     int x, int y, int width, int height)
{				/* update image on the graphics window. */
#ifdef USE_THREADED_UPDATE
    pthread_t my_thread;
#endif

    assert(display != NULL);
    assert(pixmap  != NULL);
    assert(be      != NULL);

    /* clipping */
    if (width  < 0) { x += width ; width  *= -1; }
    if (height < 0) { y += height; height *= -1; }
    if (x      < 0) { width  += x; x       =  0; }
    if (y      < 0) { height += y; y       =  0; }
    if ((width  = MIN(width , pixmap->width  - x)) <= 0 ||
	(height = MIN(height, pixmap->height - y)) <= 0)
	return;

    if (be->ximage.data == NULL)	/* 1st call */
	_window_be_ximage_init(&be->ximage, pixmap);

#ifdef USE_THREADED_UPDATE
    if (!pthread_equal(my_thread = pthread_self(), be->thread)) {
	if (pthread_join(be->thread, NULL))	/* failed thread termination. */
	    _window_be_error(__func__, ERR_THREAD_JOIN);
	be->thread = my_thread;
    }
    be->arg[0] =     x; be->arg[1] =      y;
    be->arg[2] = width; be->arg[3] = height;
#endif

    _window_be_ximage_update(&be->ximage, pixmap, x, y, width, height);

#ifdef USE_THREADED_UPDATE
    if (pthread_create(&be->thread, NULL,
			_window_be_update_image_slave, be))	/* failed thread creation. */
	_window_be_error(__func__, ERR_THREAD_CREATE);
#else				/*......................................*/
    XPutImage   (display, be->pixmap, be->gc, &be->ximage,
		 x, y, x, y, width, height);
    XClearArea  (display, be->main_window, x, y, width, height, False);
    env[EV_ASYNC] ? XFlush(display) : XSync(display, False);
#endif

    return;
}

/*======================================================================*/
void _window_be_rename(window_be_t be, const char *window_name)
{				/* rename a graphics window.            */
    assert(display     != NULL);
    assert(be          != NULL);
    assert(window_name != NULL);

#ifdef USE_THREADED_UPDATE
    XLockDisplay  (display);
#endif
    XStoreName    (display, be->base_window, window_name);
    XSetIconName  (display, be->base_window, window_name);
#ifdef USE_THREADED_UPDATE
    XUnlockDisplay(display);
#endif

    return;
}

/*======================================================================*/
window_input_t _window_be_get_input(window_be_t be, bool sync)
/* <NOTE>: XWindowEvent and XCheckWindowEvent functions cannot catch
 * client message events. This is because no appropriate event mask is
 * given for client message events. To catch client message events,
 * XIfEvent and XCheckIfEvent functions should be used instead.
 */
#ifdef USE_THREADED_UPDATE
{				/* get an X11 input event.              */
    XEvent xevent;
    window_input_t input = { -1, 0, 0, 0 };	/* device, code, x, y   */

    assert(display != NULL);
    assert(be      != NULL);

    while (1) {			/* polling loop */
	XLockDisplay  (display);
	do {
	    if (XCheckIfEvent(display, &xevent,
		_window_be_event_predicate, (XPointer) &be->base_window))
		_window_be_event_input(&input, &xevent);
	    else
		input.device = WD_Null;
	} while (input.device < 0);
	XUnlockDisplay(display);
	if (!sync || input.device != WD_Null) break;
	_window_be_dsleep(0.01);	/* 0.01sec. micro sleep to avoid busy wait. */
    }

    return input;
}
#else				/*......................................*/
{				/* get an X11 input event.              */
    XEvent xevent;
    window_input_t input = { -1, 0, 0, 0 };	/* device, code, x, y   */

    assert(display != NULL);
    assert(be      != NULL);

    if (sync) {			/* Blocking I/O     */
	do {
	    XIfEvent(display, &xevent,
		_window_be_event_predicate, (XPointer) &be->base_window);
	    _window_be_event_input(&input, &xevent);
	} while (input.device != WD_KeyBoard &&
		 input.device != WD_Mouse);
    } else {			/* Non-blocking I/O */
	do {
	    if (XCheckIfEvent(display, &xevent,
		_window_be_event_predicate, (XPointer) &be->base_window))
		_window_be_event_input(&input, &xevent);
	    else
		input.device = WD_Null;
	} while (input.device < 0);
    }

    return input;
}
#endif

/*======================================================================*/
window_input_t _window_be_query_pointer(window_be_t be)
{				/* query current pointer position.      */
    unsigned int mask;
    int        xx, yy;
    Window      v,  w;
    window_input_t input = { WD_Mouse, EXIT_SUCCESS, 0, 0 };	/* device, code, x, y */

    assert(display != NULL);
    assert(be      != NULL);

#ifdef USE_THREADED_UPDATE
    XLockDisplay  (display);
#endif
    if (!XQueryPointer(display, be->main_window,
		       &v, &w, &xx, &yy, &input.x, &input.y, &mask)) {
	input.code = EXIT_FAILURE;
	input.x    = input.y =  0;
    }
#ifdef USE_THREADED_UPDATE
    XUnlockDisplay(display);
#endif

    return input;
}

/*======================================================================*/
static void _window_be_init(void)
{				/* initialize X11.                      */
    int i, j, k, nvisuals;
    XVisualInfo *xvi_table, xvi_template;
    const int depth_table[] = { 24, 16, 15 },	/* support 24/16/15bpp depth.    */
	      class_table[] = { TrueColor  };	/* support TrueColor class only. */
    const long xvi_mask   =
	VisualScreenMask | VisualClassMask | VisualDepthMask;

    assert(display == NULL);

#ifdef USE_THREADED_UPDATE
    if (!XInitThreads())
	_window_be_error(__func__, ERR_THREAD_INIT);
#endif

    if ((display = XOpenDisplay(NULL)) == NULL)
	_window_be_error(__func__, ERR_OPEN_DISPLAY);

    root_window         = XDefaultRootWindow(display);
    screen              = XDefaultScreen    (display);
    depth               = 0;
    xvi_template.screen = screen;

    for (i = 0; i < TABLE_SIZE(depth_table); i++) {	/* search appropriate visual class. */
	xvi_template.depth = depth_table[i];
	for (j = 0; j < TABLE_SIZE(class_table); j++) {
#ifdef __cplusplus
	    xvi_template.c_class = class_table[j];
#else
	    xvi_template.class   = class_table[j];
#endif
	    if ((xvi_table = XGetVisualInfo(display, xvi_mask,
					    &xvi_template, &nvisuals)) != NULL) {
		if (depth_table[i] > 16)	/* 24bpp */
		    for (k = 0; j < nvisuals; k++)
			if (xvi_table[k].visual->red_mask   == 0x00ff0000 &&
			    xvi_table[k].visual->green_mask == 0x0000ff00 &&
			    xvi_table[k].visual->blue_mask  == 0x000000ff) {
			    depth  = depth_table[i];
			    visual =   xvi_table[k].visual;
			    break;
			}
		if (depth == 0) {
		    depth  = depth_table[i];
		    visual =   xvi_table[0].visual;
		}
		XFree(xvi_table);
		break;
	    }
	}
	if (depth != 0) break;
    }

    if (depth == 0)	/* cannot find appropriate visual class. */
	_window_be_error(__func__, ERR_VISUAL_CLASS);

    colormap = XCreateColormap(display, root_window, visual, AllocNone);
    XInstallColormap(display, colormap);

    if ((env  = MALLOC(EV_TABLE_SIZE, char *)) == NULL ||
#ifdef PROCEED_CLIENT_MESSAGE
	(atom = MALLOC(CM_TABLE_SIZE, Atom  )) == NULL ||
#endif
	atexit(_window_be_fin) != 0)	/* failed atexit call.   */
	_window_be_error(__func__, ERR_SYSTEM);

#ifdef PROCEED_CLIENT_MESSAGE
    /* setting up for client messages */
    atom[CM_PROTOCOLS    ] = XInternAtom(display, "WM_PROTOCOLS"    , False);
    atom[CM_DELETE_WINDOW] = XInternAtom(display, "WM_DELETE_WINDOW", False);
#endif

    /* setting up with environment variables */
    env[EV_RES_NAME          ] = getenv("LIBPIXMAP_X11_RES_NAME"          );
    env[EV_RES_CLASS         ] = getenv("LIBPIXMAP_X11_RES_CLASS"         );
    env[EV_RESIZABLE_WINDOW  ] = getenv("LIBPIXMAP_X11_RESIZABLE_WINDOW"  );
    env[EV_ASYNC             ] = getenv("LIBPIXMAP_X11_ASYNC"             );
#ifdef PROCEED_CLIENT_MESSAGE
    env[EV_DONT_DELETE_WINDOW] = getenv("LIBPIXMAP_X11_DONT_DELETE_WINDOW");
#endif

    return;
}

/*======================================================================*/
static void _window_be_fin(void)
{				/* finalize X11.                        */
    assert(display != NULL);

#ifdef PROCEED_CLIENT_MESSAGE
    free(atom);
#endif
    free(env);

    XUninstallColormap(display, colormap);
    XFreeColormap     (display, colormap);
    XCloseDisplay     (display);

    display = NULL;

    return;
}

/*======================================================================*/
static void _window_be_ximage_init(XImage *ximage, pixmap_t *pixmap)
{				/* initialize internal XImage data.     */
    int word;

    word = (depth > 16) ? 4 : 2;	/* pixel word size in XImage    */

    ximage->width            = pixmap->width;
    ximage->height           = pixmap->height;
    ximage->xoffset          = 0;
    ximage->format           = ZPixmap;
    ximage->bitmap_bit_order =
	ximage->byte_order   = MSBFirst;
    ximage->depth            = depth;
    ximage->bytes_per_line   = word * pixmap->width;
    ximage->bits_per_pixel   = ximage->bitmap_unit =
	ximage->bitmap_pad   = word * 8;
    ximage->red_mask         = visual->red_mask;
    ximage->green_mask       = visual->green_mask;
    ximage->blue_mask        = visual->blue_mask;

#ifdef USE_SHARED_PIXEL_DATA
    if (visual->red_mask   == 0x00ff0000 &&
	visual->green_mask == 0x0000ff00 &&
	visual->blue_mask  == 0x000000ff) {	/* XImage shares pixel data with pixmap_t. */
	ximage->data = (char *) pixmap->data;
    } else
#endif
    if ((ximage->data = MALLOC((size_t) ximage->bytes_per_line *
					ximage->height, char)) == NULL)
	_window_be_error(__func__, ERR_SYSTEM);

    XInitImage(ximage);

    return;
}

/*======================================================================*/
static void _window_be_ximage_update(XImage *ximage, pixmap_t *pixmap,
				     int x, int y, int width, int height)
{				/* convert a pixmap image to the XImage. */
    int i, j;
    static int  r_bits = 0, r_offset = 0,
		g_bits = 0, g_offset = 0,
		b_bits = 0, b_offset = 0, word = 0;

    assert(ximage != NULL);
    assert(pixmap != NULL);
    assert(x >= 0 && y >= 0 && width > 0 && height > 0);

#ifdef  USE_SHARED_PIXEL_DATA
    if (visual->red_mask   == 0x00ff0000 &&
	visual->green_mask == 0x0000ff00 &&
	visual->blue_mask  == 0x000000ff)	/* No need to update: XImage shares pixel data with pixmap_t. */
	return;
#endif

    if (depth != r_bits + g_bits + b_bits) {	/* 1st call */
	_window_be_mask_info(visual->red_mask  , &r_bits, &r_offset);
	_window_be_mask_info(visual->green_mask, &g_bits, &g_offset);
	_window_be_mask_info(visual->blue_mask , &b_bits, &b_offset);
	assert(depth == r_bits + g_bits + b_bits);
	word = (depth > 16) ? 4 : 2;		/* pixel word size in XImage */
    }

    if (word == 4) {		/* XImage uses 4byte pixel (=24bpp). */
#ifndef USE_SHARED_PIXEL_DATA
	if (visual->red_mask   == 0x00ff0000 &&
	    visual->green_mask == 0x0000ff00 &&
	    visual->blue_mask  == 0x000000ff) {	/* XImage is 00RRGGBB format. */
#if SIZEOF_PIXEL_T == 4
	    if (width == pixmap->width)		/* "width == pixmap->width" means "x == 0". */
		memcpy(&ximage->data[(size_t) y * width * word],
		       &pixmap->data[(size_t) y * width], (size_t) width * height * word);
	    else
#endif
	    for (j = y; j <  y + height; j++)
		for (i = x; i <  x + width; i++) {
		    size_t ij = (size_t) j * pixmap->width + i;
		    ximage->data[word * ij    ] = 0x00;
		    ximage->data[word * ij + 1] = pixmap->data[ij].r;
		    ximage->data[word * ij + 2] = pixmap->data[ij].g;
		    ximage->data[word * ij + 3] = pixmap->data[ij].b;
		}
	} else {				/* XImage is non-00RRGGBB format. */
#endif
	    for (j = y; j <  y + height; j++)
		for (i = x; i <  x + width; i++) {
		    size_t ij = (size_t) j * pixmap->width + i;
		    unsigned int pixel = ((unsigned int) pixmap->data[ij].r << r_offset) |
					 ((unsigned int) pixmap->data[ij].g << g_offset) |
					 ((unsigned int) pixmap->data[ij].b << b_offset);
		    ximage->data[word * ij    ] = (char) ((pixel >> 24) & 0xff);
		    ximage->data[word * ij + 1] = (char) ((pixel >> 16) & 0xff);
		    ximage->data[word * ij + 2] = (char) ((pixel >>  8) & 0xff);
		    ximage->data[word * ij + 3] = (char) ((pixel      ) & 0xff);
		}
#ifndef USE_SHARED_PIXEL_DATA
	}
#endif
    } else {			/* XImage uses 2byte pixel (=16 or 15bpp). */
	const int rs = 8 - r_bits,
		  gs = 8 - g_bits,
		  bs = 8 - b_bits;
	for (j = y; j <  y + height; j++)
	    for (i = x; i <  x + width; i++) {
		size_t ij = (size_t) j * pixmap->width + i;
		unsigned int pixel = (((unsigned int) pixmap->data[ij].r >> rs) << r_offset) |
				     (((unsigned int) pixmap->data[ij].g >> gs) << g_offset) |
				     (((unsigned int) pixmap->data[ij].b >> bs) << b_offset);
		ximage->data[word * ij    ] = (char) ((pixel >> 8) & 0xff);
		ximage->data[word * ij + 1] = (char) ((pixel     ) & 0xff);
	    }
    }

    return;
}

/*======================================================================*/
#define lowbit(x)	((x)&(~(x)+0x01))
/* Term Definition:
   ================
                    length      offset
      <---9---><<=====16=====>><<=7=>>
      00000000011111111111111110000000  <- bit mask
      MSB                          LSB
 */
static void _window_be_mask_info(unsigned long mask, int *length, int *offset)
{				/* bit mask information                 */
    register unsigned long lbit;

    assert(length != NULL);
    assert(offset != NULL);

    lbit = lowbit(mask);

    for (*offset = 0; 0x01 << *offset != lbit; (*offset)++, mask >>= 0x01);
    for (*length = 0; mask >> *length != 0x00; (*length)++);

    return;
}

/*======================================================================*/
static Bool _window_be_event_predicate(Display *dp, XEvent *xevent, XPointer arg)
{				/* X11 event predicate function.        */
    return (xevent->xany.window == *((Window *) arg)) ? True : False;
}

/*======================================================================*/
static void _window_be_event_input(window_input_t *input, XEvent *xevent)
{				/* convert an XEvent to the window_input_t. */
    char buf[256];
    KeySym keysym;

    assert(xevent != NULL);
    assert(input  != NULL);
    assert(input->device < 0);

#ifdef DEBUG
    _window_be_event_info(xevent, __func__);
#endif

    switch (xevent->type) {
    case (KeyPress):		/* keyboard press */
	XLookupString((XKeyEvent *) xevent,
		      buf, sizeof(buf), &keysym, NULL);
	if ((input->code = _window_be_event_keycode(keysym, buf)) != WK_Null)
	    input->device = WD_KeyBoard;
	break;
    case (KeyRelease):		/* keyboard release (to be ignored.) */
	break;
    case (ButtonPress):		/* mouse input */
	input->device = WD_Mouse;
#if 0
	switch (xevent->xbutton.button) {
	case (Button1): input->code = WM_Button1; break;
	case (Button2): input->code = WM_Button2; break;
	case (Button3): input->code = WM_Button3; break;
	case (Button4): input->code = WM_Button4; break;
	case (Button5): input->code = WM_Button5; break;
	default:        input->code = WM_Null;    break;
	}
#else
	input->code   = xevent->xbutton.button;
#endif
	input->x      = xevent->xbutton.x;
	input->y      = xevent->xbutton.y;
	break;
    case (ButtonRelease):	/* mouse button release */
	input->device = WD_Mouse;
	input->code   = WM_Release;
	input->x      = xevent->xbutton.x;
	input->y      = xevent->xbutton.y;
	break;
    case (MotionNotify):	/* mouse motion */
	input->device = WD_Mouse;
	input->code   =
#ifdef DETECT_POINTER_MOTION_NOTIFY
	    (xevent->xmotion.state & (Button1Mask | Button2Mask | Button3Mask |
				      Button4Mask | Button5Mask)) ? WM_Drag : WM_Motion;
#else
	    WM_Drag;
#endif
	input->x      = xevent->xmotion.x;
	input->y      = xevent->xmotion.y;
	break;
    case (ClientMessage):	/* client messages */
#ifdef PROCEED_CLIENT_MESSAGE
	if (xevent->xclient.message_type == atom[CM_PROTOCOLS    ] &&
	    xevent->xclient.data.l[0]    == atom[CM_DELETE_WINDOW] &&
	    env[EV_DONT_DELETE_WINDOW]   == NULL)
	    exit(EXIT_SUCCESS);	/* normal termination */
#endif
	break;
    case (MappingNotify):	/* keyboard mapping notify */
	XRefreshKeyboardMapping((XMappingEvent *) xevent);
	break;
    default:
	assert(false);		/* should NEVER reach here. */
	break;
    }

    assert(input->device != WD_Mouse ||
	  (input->code   >= 0x00     && input->code <= 0x07));

#ifdef DEBUG
    if (input->device >= 0)	/* the processed event is not user input if input->device < 0. */
	fprintf(stderr, "DEBUG(%s): device=%c, code=0x%02x, (x,y)=(%d,%d)\n",
			__func__, "NKM"[input->device], input->code, input->x, input->y);
#endif

    return;
}

/*======================================================================*/
static int _window_be_event_keycode(KeySym keysym, char *buf)
{				/* convert a X11 key symbol to the key code. */
    int code = WK_Null;

    assert(buf != NULL);

    switch (keysym) {
    case (XK_Right    ): case (XK_KP_Right    ): code = WK_Right   ; break;
    case (XK_Left     ): case (XK_KP_Left     ): code = WK_Left    ; break;
    case (XK_Up       ): case (XK_KP_Up       ): code = WK_Up      ; break;
    case (XK_Down     ): case (XK_KP_Down     ): code = WK_Down    ; break;
    case (XK_Page_Up  ): case (XK_KP_Page_Up  ): code = WK_PageUp  ; break;
    case (XK_Page_Down): case (XK_KP_Page_Down): code = WK_PageDown; break;
    case (XK_Home     ): case (XK_KP_Home     ): code = WK_Home    ; break;
    case (XK_End      ): case (XK_KP_End      ): code = WK_End     ; break;
    case (XK_Pause    ):                         code = WK_Pause   ; break;
    case (XK_KP_Delete):                         code = WK_Delete  ; break;
    default:                                     code = buf[0]     ; break;
    }

    return code;
}

/*======================================================================*/
static void _window_be_error(const char *func, const int err_code)
{				/* error handler                        */
    const char *err_message[] = {
	"unknown error",
	"system error",
	"cannot open X11 display",
	"support 24/16/15bpp TrueColor visual class only",
	"cannot initialize Xlib support for concurrent threads",
	"cannot create a new thread",
	"cannot join with a terminated thread"
    };

    assert(func != NULL);
    assert(err_code >= 0 && err_code < TABLE_SIZE(err_message));

    if (errno != 0 && err_code == ERR_SYSTEM) {
	perror(func);
    } else {
	fprintf(stderr, "%s: %s.\n", func, err_message[err_code]);
    }

#ifdef DEBUG
    if (err_code == ERR_VISUAL_CLASS)
	_window_be_default_visual_info();
#endif

    exit(EXIT_FAILURE);

    return;
}

#ifdef USE_THREADED_UPDATE
/*======================================================================*/
static int _window_be_dsleep(double tm)
{				/* micro-sleep function                 */
    struct timespec spec;

    assert(tm >= 0.0);

    spec.tv_sec  = (time_t) tm;
    spec.tv_nsec = (tm - spec.tv_sec) * 1E9;

    if (nanosleep(&spec, NULL) != 0)
	return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/*======================================================================*/
static void *_window_be_update_image_slave(void *p)
{				/* thread slave function to update the graphics window. */
    window_be_t be;

    be = (window_be_t) p;

    assert(display != NULL);
    assert(be      != NULL);
    assert(pthread_equal(pthread_self(), be->thread));

    XLockDisplay  (display);
    XPutImage     (display, be->pixmap, be->gc, &be->ximage,
		   be->arg[0], be->arg[1],
		   be->arg[0], be->arg[1], be->arg[2], be->arg[3]);
    XClearArea    (display, be->main_window,
		   be->arg[0], be->arg[1], be->arg[2], be->arg[3], False);
    env[EV_ASYNC] ? XFlush(display) : XSync(display, False);
    XUnlockDisplay(display);

    return NULL;
}
#endif

#ifdef DEBUG
/*======================================================================*/
static void _window_be_default_visual_info(void)
{				/* write out X11 default visual information. */
    Visual *vis;
    const char *name_of[] = {	/* visual class names (from X11/X.h) */
	"StaticGray" , "GrayScale", "StaticColor",
	"PseudoColor", "TrueColor", "DirectColor"
    };

    assert(display != NULL);

#ifdef USE_THREADED_UPDATE
    XLockDisplay  (display);
#endif

    vis = DefaultVisual(display, screen);

#ifdef __cplusplus
    assert(vis->c_class >= 0 && vis->c_class < TABLE_SIZE(name_of));
#else
    assert(vis->class   >= 0 && vis->class   < TABLE_SIZE(name_of));
#endif

    fprintf(stderr,
	    "X11 default visual:\n"
	    "\tid   =0x%02x\n"
	    "\tclass=%s\n"
	    "\tdepth=%dbpp\n"
	    "\tred, green, blue masks=0x%08x, 0x%08x, 0x%08x\n",
	    (unsigned int) vis->visualid,
#ifdef __cplusplus
	    name_of[vis->c_class],
#else
	    name_of[vis->class  ],
#endif
	    DefaultDepth(display, screen),  (unsigned int) vis->red_mask,
	    (unsigned int) vis->green_mask, (unsigned int) vis->blue_mask);

#ifdef USE_THREADED_UPDATE
    XUnlockDisplay(display);
#endif

    return;
}

/*======================================================================*/
static void _window_be_event_info(XEvent *xevent, const char *func)
{				/* write out X11 event information.     */
    int type = 0;
    const char *name_of[] = {	/* Xevent name (from X11/X.h).          */
	"Unknown"         , "Unknown"         , "KeyPress"        ,
	"KeyRelease"      , "ButtonPress"     , "ButtonRelease"   ,
	"MotionNotify"    , "EnterNotify"     , "LeaveNotify"     ,
	"FocusIn"         , "FocusOut"        , "KeymapNotify"    ,
	"Expose"          , "GraphicsExpose"  , "NoExpose"        ,
	"VisibilityNotify", "CreateNotify"    , "DestroyNotify"   ,
	"UnmapNotify"     , "MapNotify"       , "MapRequest"      ,
	"ReparentNotify"  , "ConfigureNotify" , "ConfigureRequest",
	"GravityNotify"   , "ResizeRequest"   , "CirculateNotify" ,
	"CirculateRequest", "PropertyNotify"  , "SelectionClear"  ,
	"SelectionRequest", "SelectionNotify" , "ColormapNotify"  ,
	"ClientMessage"   , "MappingNotify"   , "GenericEvent"
    };

    assert(display != NULL);
    assert(xevent  != NULL);
    assert(func    != NULL);
    assert(TABLE_SIZE(name_of) == LASTEvent);

    if (xevent->type >= 0 && xevent->type < LASTEvent)
	type = xevent->type;

    fprintf(stderr, "DEBUG(%s): detected %s event.\n",
					func, name_of[type]);

    return;
}
#endif

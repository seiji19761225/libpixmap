/*
 * window.h: libpixmap window system interface module
 * (c)2004-2009,2011-2015 Seiji Nishimura
 * $Id: window.h,v 1.1.1.4 2020/07/29 00:00:00 seiji Exp seiji $
 */

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <libpixmap/pixmap.h>

/* device ID  ("WD_" stands for Window system Device ID. ) */
#define WD_Null		0x00
#define WD_KeyBoard	0x01
#define WD_Mouse	0x02
/* key   code ("WK_" stands for Window system Key   code.) */
#define WK_Null		0x00
#define WK_Home		0x01
#define WK_PageUp	0x02
#define WK_Pause	0x03
#define WK_End		0x05
#define WK_PageDown	0x06
#define WK_BackSpace	0x08	/* == '\b' */
#define WK_Tab		0x09	/* == '\t' */
#define WK_Enter	0x0d	/* == '\r' */
#define WK_ESC		0x1b
#define WK_Right	0x1c
#define WK_Left		0x1d
#define WK_Up		0x1e
#define WK_Down		0x1f
#define WK_Delete	0x7f
/* mouse code ("WM_" stands for Window system Mouse code.) */
#define WM_Null		0x00
#define WM_Button1	0x01
#define WM_Button2	0x02
#define WM_Button3	0x03
#define WM_Button4	0x04
#define WM_Button5	0x05
#define WM_Drag		0x06
#define WM_Release	0x07
#define WM_Motion	0x00	/* == WM_Null    */
#define WM_WheelUp	0x04	/* == WM_Button4 */
#define WM_WheelDown	0x05	/* == WM_Button5 */

/* data type -----------------------------------------------------------*/

typedef struct {	/* GFX window */
    pixmap_t pixmap;
    void        *be;
} window_t;

/* prototypes ----------------------------------------------------------*/

#ifdef __WINDOW_INTERNAL__
#define  WINDOW_API
#else
#define  WINDOW_API extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

WINDOW_API void window_open           (window_t *, int  , int  , const char *);
WINDOW_API void window_close          (window_t *);
WINDOW_API void window_discard_inputs (window_t *);
WINDOW_API void window_get_input      (window_t *, bool , int *, int *, int *, int *);
WINDOW_API void window_get_subimage   (window_t *, int  , int  , pixmap_t   *, int, int);
WINDOW_API void window_rename         (window_t *, const char *);
WINDOW_API void window_update_subimage(window_t *, int  , int  , int  , int);
WINDOW_API int  window_query_pointer  (window_t *, int *, int *);
WINDOW_API int  window_load_pnmfile   (window_t *, const char *);
WINDOW_API int  window_load_pnmfp     (window_t *, FILE *);

#if        defined(__WINDOW_INTERNAL__) || !defined(NDEBUG)
WINDOW_API void     window_clear_image    (window_t *, pixel_t);
WINDOW_API void     window_clear_subimage (window_t *, pixel_t  , int , int  , int  , int);
WINDOW_API void     window_draw_arc       (window_t *, pixel_t  , int , int  , int  , int, double, double);
WINDOW_API void     window_draw_arrow     (window_t *, pixel_t  , bool, bool , int  , int, int, int, int, int, int);
WINDOW_API void     window_draw_ellipse   (window_t *, pixel_t  , int , int  , int  , int);
WINDOW_API void     window_draw_line      (window_t *, pixel_t  , int , int  , int  , int);
WINDOW_API void     window_draw_polygon   (window_t *, pixel_t  , int , int *, int *);
WINDOW_API void     window_draw_triangle  (window_t *, pixel_t  , int , int  , int  , int, int, int);
WINDOW_API void     window_draw_string    (window_t *, pixel_t  , int , int  , const char *);
WINDOW_API void     window_fill_arc       (window_t *, pixel_t  , bool, int  , int  , int  , int, double, double);
WINDOW_API void     window_fill_ellipse   (window_t *, pixel_t  , int , int  , int  , int);
WINDOW_API void     window_fill_polygon   (window_t *, pixel_t  , int , int *, int *);
WINDOW_API void     window_fill_triangle  (window_t *, pixel_t  , int , int  , int  , int, int, int);
WINDOW_API void     window_get_pixel      (window_t *, pixel_t *, int , int);
WINDOW_API pixel_t *window_get_pointer    (window_t *);
WINDOW_API void     window_get_size       (window_t *, int *, int *);
WINDOW_API void     window_get_image      (window_t *, pixmap_t *);
WINDOW_API void     window_invert_image   (window_t *);
WINDOW_API void     window_invert_subimage(window_t *, int , int, int , int);
WINDOW_API void     window_put_pixel      (window_t *, pixel_t  , int , int);
WINDOW_API void     window_put_image      (window_t *, pixmap_t *);
WINDOW_API void     window_put_subimage   (window_t *, int  , int  , pixmap_t   *, int, int, int, int);
WINDOW_API void     window_update_image   (window_t *);
WINDOW_API int      window_write_pnmfile  (window_t *, const char *);
WINDOW_API int      window_write_pnmfp    (window_t *, FILE *);
#else	/* defined(__WINDOW_INTERNAL__) || !defined(NDEBUG) ............*/
	/* macro functions for short circuit optimization   ............*/
#define window_clear_image(win,p)			pixmap_clear_image(&(win)->pixmap,p)
#define window_clear_subimage(win,p,x,y,w,h)		pixmap_clear_subimage(&(win)->pixmap,p,x,y,w,h)
#define window_draw_arc(win,p,xc,yc,rx,ry,th,ph)	pixmap_draw_arc(&(win)->pixmap,p,xc,yc,rx,ry,th,ph)
#define window_draw_arrow(win,p,d,s,t,w,l,xs,ys,xe,ye)	pixmap_draw_arrow(&(win)->pixmap,p,d,s,t,w,l,xs,ys,xe,ye)
#define window_draw_ellipse(win,p,xc,yc,rx,ry)		pixmap_draw_ellipse(&(win)->pixmap,p,xc,yc,rx,ry)
#define window_draw_line(win,p,xs,ys,xe,ye)		pixmap_draw_line(&(win)->pixmap,p,xs,ys,xe,ye)
#define window_draw_polygon(win,p,n,x,y)		pixmap_draw_polygon(&(win)->pixmap,p,n,x,y)
#define window_draw_triangle(win,p,x0,y0,x1,y1,x2,y2)	pixmap_draw_triangle(&(win)->pixmap,p,x0,y0,x1,y1,x2,y2)
#define window_draw_string(win,p,x,y,s)			pixmap_draw_string(&(win)->pixmap,p,x,y,s)
#define window_fill_arc(win,p,flg,xc,yc,rx,ry,th,ph)	pixmap_fill_arc(&(win)->pixmap,p,flg,xc,yc,rx,ry,th,ph)
#define window_fill_ellipse(win,p,xc,yc,rx,ry)		pixmap_fill_ellipse(&(win)->pixmap,p,xc,yc,rx,ry)
#define window_fill_polygon(win,p,n,x,y)		pixmap_fill_polygon(&(win)->pixmap,p,n,x,y)
#define window_fill_triangle(win,p,x0,y0,x1,y1,x2,y2)	pixmap_fill_triangle(&(win)->pixmap,p,x0,y0,x1,y1,x2,y2)
#define window_get_pixel(win,p,x,y)			pixmap_get_pixel(&(win)->pixmap,p,x,y)
#define window_get_pointer(win)				pixmap_get_pointer(&(win)->pixmap)
#define window_get_size(win,x,y)			pixmap_get_size(&(win)->pixmap,x,y)
#define window_get_image(win,pmap)			window_get_subimage(win,0,0,pmap,(win)->pixmap.width,(win)->pixmap.height)
#define window_invert_image(win)			pixmap_invert_image(&(win)->pixmap)
#define window_invert_subimage(win,x,y,w,h)		pixmap_invert_subimage(&(win)->pixmap,x,y,w,h)
#define window_put_pixel(win,p,x,y)			pixmap_put_pixel(&(win)->pixmap,p,x,y)
#define window_put_image(win,pmap)			pixmap_copy_image(pmap,&(win)->pixmap)
#define window_put_subimage(win,wx,wy,pmap,px,py,w,h)	pixmap_copy_subimage(pmap,px,py,&(win)->pixmap,wx,wy,w,h)
#define window_update_image(win)			window_update_subimage(win,0,0,(win)->pixmap.width,(win)->pixmap.height)
#define window_write_pnmfile(win,fname)			pixmap_write_pnmfile(&(win)->pixmap,fname)
#define window_write_pnmfp(win,fp)			pixmap_write_pnmfp(&(win)->pixmap,fp)
#endif	/* defined(__WINDOW_INTERNAL__) || !defined(NDEBUG) ............*/

#ifdef __cplusplus
}
#endif

#undef WINDOW_API
#endif

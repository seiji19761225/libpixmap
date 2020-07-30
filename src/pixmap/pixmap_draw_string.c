/*
 * pixmap_draw_string.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_draw_string.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */
/*
 *  Changes for banner(1)
 *
 *  @(#)Copyright (c) 1995, Simon J. Gerraty.
 *  
 *  This is free software.  It comes with NO WARRANTY.
 *  Permission to use, modify and distribute this source code 
 *  is granted subject to the following conditions.
 *  1/ that the above copyright notice and this notice 
 *  are preserved in all copies and that due credit be given 
 *  to the author.  
 *  2/ that any changes to this code are clearly commented 
 *  as such so that the author does not get blamed for bugs 
 *  other than his own.
 *  
 *  Please send copies of changes and bug-fixes to:
 *  sjg@zen.void.oz.au
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "pixmap_internal.h"
#include "font.h"

#if ((FONT_SET == 0) && (FONT_WIDTH != WIDTH    )) || \
    ((FONT_SET != 0) && (FONT_WIDTH != WIDTH + 1)) || (FONT_HEIGHT != (HEIGHT + DROP))
#error Font size is inconsistent. Please check both font.h and pixmap.h.
#endif

#define TRC(q)		(((q)-' ')&0177)

/* internal functions */
static char *_pixmap_draw_string_scnline(int, char *);
static int   _pixmap_draw_string_dropit (int);

/*======================================================================*/
void pixmap_draw_string(pixmap_t *pixmap, pixel_t pixel, int xs, int ys,
			const char *str)
{				/* draw a string.                       */
    int d, i, j, k;
    char c, cc, *bp, *sp, *buf;

    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);
    assert(str != NULL);

    if ((buf = (char *) calloc(FONT_WIDTH * strlen(str) + 1,
					sizeof(char))) == NULL)
	pixmap_abort(__func__);

    for (j = 0; j < FONT_HEIGHT; j++) {
	for (bp = buf, sp = (char *) str; (cc = *sp++) != '\0'; *bp++ = BACKGND) {
	    if (cc < ' ' || cc > 0x7f)	/* if (!isprint(cc)) */
		cc = INVALID;		/* rub-out           */
	    c = TRC(cc);
	    d = _pixmap_draw_string_dropit(c);
	    if ((!d && j >= HEIGHT) || (d && j < DROP)) {
		for (k = WIDTH; --k; *bp++ = BACKGND);
	    } else {
		bp = _pixmap_draw_string_scnline(scnkey[c][j - d], bp);
	    }
#if FONT_SET != 0	/* <sjg> */
	    *bp++ = BACKGND;
#endif
	}
	while (*--bp == BACKGND && bp >= buf);
	*++bp = '\0';
	for (i = 0; buf[i] == BACKGND || buf[i] == FOREGND; i++)
	    if (buf[i] == FOREGND)
		pixmap_put_pixel(pixmap, pixel, xs + i, ys + j);
    }

    free(buf);

    return;
}

/*----------------------------------------------------------------------*/
static char *_pixmap_draw_string_scnline(int key, char *p)
{				/* string scanline                      */
    int i = WIDTH;

    while (--i)
	*p++ = ((key <<= 1) & 0200) ? FOREGND : BACKGND;

    return p;
}

/*----------------------------------------------------------------------*/
static int _pixmap_draw_string_dropit(int c)
{				/* string drop detection                */
    switch (c) {
    case TRC('_'): case TRC(';'):
    case TRC(','): case TRC('g'):
    case TRC('j'): case TRC('p'):
    case TRC('q'): case TRC('y'):
	return DROP;
    default:
	break;
    }

    return 0;
}

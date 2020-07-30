/*
 * pixmap_fill_triangle.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_fill_triangle.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "pixmap_internal.h"

/*======================================================================*/
void pixmap_fill_triangle(pixmap_t *pixmap, pixel_t pixel,
			  int x0, int y0, int x1, int y1, int x2, int y2)
#if 0
{				/* draw a filled triangle.              */
    int xx[3], yy[3];

    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);

    xx[0] = x0; xx[1] = x1; xx[2] = x2;
    yy[0] = y0; yy[1] = y1; yy[2] = y2;

    pixmap_fill_polygon(pixmap, pixel, 3, xx, yy);

    return;
}
#else				/*......................................*/
{				/* draw a filled triangle.              */
    int ax1, bx1, dx1, dy1, ex1, hx1, mx1,
	ax2, bx2, dx2, dy2, ex2, hx2, mx2, tt;

    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);

#ifdef DRAW_OUTLINE
    pixmap_draw_triangle(pixmap, pixel, x0, y0, x1, y1, x2,y2);
#endif

    /* sort verteces for y direction: y0 <= y1 <= y2 */
    if (y1 < y0) {
	tt = x0; x0 = x1; x1 = tt;
	tt = y0; y0 = y1; y1 = tt;
    }
    if (y2 < y0) {
	tt = x0; x0 = x2; x2 = tt;
	tt = y0; y0 = y2; y2 = tt;
    }
    if (y2 < y1) {
	tt = x1; x1 = x2; x2 = tt;
	tt = y1; y1 = y2; y2 = tt;
    }

    if ((dy2 = y2 - y0) <= 0)
	return;

    mx2 = (((dx2 = x2 - x0) >= 0) ? dx2 : (dx2 - dy2 + 1)) / dy2;
    ax2 = (mx2 * dy2 - dx2) << 1;
    bx2 = (ex2 = dy2)       << 1;
    hx2 = x0; tt = y0;

    if ((dy1 = y1 - y0) > 0) {	/* lower half triangle */
	mx1 = (((dx1 = x1 - x0) >= 0) ? dx1 : (dx1 - dy1 + 1)) / dy1;
	ax1 = (mx1 * dy1 - dx1) << 1;
	bx1 = (ex1 = dy1)       << 1;
	hx1 =  x0;
	do {
	    pixmap_draw_line(pixmap, pixel, hx1, tt, hx2, tt);
	    hx2 += mx2; ex2 += ax2;
	    if (ex2 <= 0) { hx2++; ex2 += bx2; }
	    hx1 += mx1; ex1 += ax1;
	    if (ex1 <= 0) { hx1++; ex1 += bx1; }
	    tt++;
	} while (--dy1 > 0);
    }

    if ((dy1 = y2 - y1) > 0) {	/* upper half triangle */
	mx1 = (((dx1 = x2 - x1) >= 0) ? dx1 : (dx1 - dy1 + 1)) / dy1;
	ax1 = (mx1 * dy1 - dx1) << 1;
	bx1 = (ex1 = dy1)       << 1;
	hx1 =  x1;
	do {
	    pixmap_draw_line(pixmap, pixel, hx1, tt, hx2, tt);
	    hx2 += mx2; ex2 += ax2;
	    if (ex2 <= 0) { hx2++; ex2 += bx2; }
	    hx1 += mx1; ex1 += ax1;
	    if (ex1 <= 0) { hx1++; ex1 += bx1; }
	    tt++;
	} while (--dy1 > 0);
    }

    return;
}
#endif

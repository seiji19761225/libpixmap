/*
 * pixmap_draw_arrow.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_draw_arrow.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <math.h>
#include <assert.h>
#include "pixmap_internal.h"

#define CENTER(a,b,c)	((2.0*(a)+(b)+(c))*0.25)

/* internal functions */
static void _pixmap_draw_arrow_head(pixmap_t *, pixel_t, bool, int, int *, int *);

/*======================================================================*/
void pixmap_draw_arrow(pixmap_t *pixmap, pixel_t pixel, bool dual, bool sharp,
			int type, int width, int length, int xs, int ys, int xe, int ye)
{				/* draw an arrow.                       */
    int x[4], y[4];
    double dx, dy, dl, sn = 0.0, cn = 1.0;

    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);

    if ((dl = hypot(dx = xe - xs,
		    dy = ye - ys)) > 0.0) {	/* calculate sin/cos.   */
	cn = dx / dl;
	sn = dy / dl;
    }

    /* draw an arrow head (destination side). */
    dx   = dl - length;
    dy   = width;
    dl   = sharp ? CENTER(dl, dx, dx) : dx;
    x[0] = xe;
    y[0] = ye;
    x[1] = xs + ROUND(dx * cn - dy * sn);
    y[1] = ys + ROUND(dx * sn + dy * cn);
    x[2] = xs + ROUND(dl * cn);
    y[2] = ys + ROUND(dl * sn);
    x[3] = xs + ROUND(dx * cn + dy * sn);
    y[3] = ys + ROUND(dx * sn - dy * cn);
    if (type == AH_TYPE2) {
	xe = x[2];
	ye = y[2];
    }
    _pixmap_draw_arrow_head(pixmap, pixel, true, type, x, y);

    if (dual) {	/* draw an arrow head (origin side). */
	dx   = length;
/*	dy   = width ; */
	dl   = sharp ? CENTER(0.0, dx, dx) : dx;
	x[0] = xs;
	y[0] = ys;
	x[1] = xs + ROUND(dx * cn - dy * sn);
	y[1] = ys + ROUND(dx * sn + dy * cn);
	x[2] = xs + ROUND(dl * cn);
	y[2] = ys + ROUND(dl * sn);
	x[3] = xs + ROUND(dx * cn + dy * sn);
	y[3] = ys + ROUND(dx * sn - dy * cn);
	if (type == AH_TYPE2) {
	    xs = x[2];
	    ys = y[2];
	}
	_pixmap_draw_arrow_head(pixmap, pixel, false, type, x, y);
    }

    pixmap_draw_line(pixmap, pixel, xs, ys, xe, ye);

    return;
}

/*----------------------------------------------------------------------*/
static void _pixmap_draw_arrow_head(pixmap_t *pixmap, pixel_t pixel,
				    bool dest, int type, int *x, int *y)
{				/* draw an arrow head.                  */
    int i;

    switch (type) {
    case (AH_TYPE7): case (AH_TYPE6):
	i = (dest == (type == AH_TYPE7)) ? 3 : 1;
	pixmap_fill_triangle(pixmap, pixel,
			     x[0], y[0], x[2], y[2], x[i], y[i]);
	break;
    case (AH_TYPE5):
	pixmap_fill_polygon(pixmap, pixel, 4, x, y);
	break;
    case (AH_TYPE4): case (AH_TYPE3):
	i = (dest == (type == AH_TYPE4)) ? 3 : 1;
	pixmap_draw_line(pixmap, pixel, x[0], y[0], x[i], y[i]);
	pixmap_draw_line(pixmap, pixel, x[2], y[2], x[i], y[i]);
	break;
    case (AH_TYPE2): case (AH_TYPE1):
	pixmap_draw_polygon(pixmap, pixel, 4, x, y);
	break;
    case (AH_TYPE0): default        :
	pixmap_draw_line(pixmap, pixel, x[0], y[0], x[1], y[1]);
	pixmap_draw_line(pixmap, pixel, x[0], y[0], x[3], y[3]);
	break;
    }

    return;
}

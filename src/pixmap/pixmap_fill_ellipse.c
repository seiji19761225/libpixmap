/*
 * pixmap_fill_ellipse.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_fill_ellipse.c,v 1.1.1.4 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "pixmap_internal.h"

/*======================================================================*/
void pixmap_fill_ellipse(pixmap_t *pixmap, pixel_t pixel,
			 int xc, int yc, int rx, int ry)
{				/* draw a filled ellipse.               */
    int i, r, x, y, x1, y1;

    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);

    if (rx == 0 || ry == 0) {
	pixmap_draw_line(pixmap, pixel, xc - rx, yc - ry, xc + rx, yc + ry);
	return;
    }

    if (rx < 0) rx *= -1;
    if (ry < 0) ry *= -1;

    if (rx > ry) {
	x = r = rx; y = 0;
	while (x >= y) {
	    x1 = (x * ry) / rx; y1 = (y * ry) / rx;
	    for (i = xc - x; i <= xc + x; i++) {
		pixmap_put_pixel(pixmap, pixel, i, yc + y1);
		pixmap_put_pixel(pixmap, pixel, i, yc - y1);
	    }
	    for (i = xc - y; i <= xc + y; i++) {
		pixmap_put_pixel(pixmap, pixel, i, yc + x1);
		pixmap_put_pixel(pixmap, pixel, i, yc - x1);
	    }
	    if ((r -= (y++ << 1) - 1) < 0)
		r += (x-- - 1) << 1;
	}
    } else {
	x = r = ry; y = 0;
	while (x >= y) {
	    x1 = (x * rx) / ry; y1 = (y * rx) / ry;
	    for (i = xc - x1; i <= xc + x1; i++) {
		pixmap_put_pixel(pixmap, pixel, i, yc + y);
		pixmap_put_pixel(pixmap, pixel, i, yc - y);
	    }
	    for (i = xc - y1; i <= xc + y1; i++) {
		pixmap_put_pixel(pixmap, pixel, i, yc + x);
		pixmap_put_pixel(pixmap, pixel, i, yc - x);
	    }
	    if ((r -= (y++ << 1) - 1) < 0)
		r += (x-- - 1) << 1;
	}
    }

    return;
}

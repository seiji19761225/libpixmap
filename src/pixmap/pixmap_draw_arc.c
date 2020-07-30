/*
 * pixmap_draw_arc.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_draw_arc.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include "pixmap_internal.h"

/*======================================================================*/
void pixmap_draw_arc(pixmap_t *pixmap, pixel_t pixel,
		     int xc, int yc, int rx, int ry, double theta, double phi)
{				/* draw an arc.                         */
    int i, n, x, y, xx, yy;
    double dt;

    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);

    if (phi < 0.0)
	theta -= (phi *= -1.0);

    if (phi >= 2.0 * M_PI) {
	pixmap_draw_ellipse(pixmap, pixel, xc, yc, rx, ry);
	return;
    }

    n  = MIN(ARC_SAMPLING_LIMIT,
	     ARC_SAMPLING_FACTOR * ROUND(phi * MAX(abs(rx), abs(ry))));
    dt = phi / n;

    pixmap_put_pixel(pixmap, pixel, x = xc + ROUND(rx * cos(theta)),
				    y = yc + ROUND(ry * sin(theta)));

    for (i = 1; i < n; i++, x = xx, y = yy) {
	xx = xc + ROUND(rx * cos(theta + i * dt));
	yy = yc + ROUND(ry * sin(theta + i * dt));
	if (x != xx || y != yy)
	    pixmap_draw_line(pixmap, pixel, x, y, xx, yy);
    }

    return;
}

/*
 * pixmap_fill_arc.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_fill_arc.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include "pixmap_internal.h"

/*======================================================================*/
void pixmap_fill_arc(pixmap_t *pixmap, pixel_t pixel, bool flag,
		     int xc, int yc, int rx, int ry, double theta, double phi)
{				/* draw a filled arc (pie slice/chord). */
    int i, m, n, xx, yy,
	x[ARC_SAMPLING_LIMIT + 1],
	y[ARC_SAMPLING_LIMIT + 1];
    double dt;

    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);

    if (phi < 0.0)
	theta -= (phi *= -1.0);

    if (phi >= 2.0 * M_PI) {
	pixmap_fill_ellipse(pixmap, pixel, xc, yc, rx, ry);
	return;
    }

    n  = MIN(ARC_SAMPLING_LIMIT,
	     ARC_SAMPLING_FACTOR * ROUND(phi * MAX(abs(rx), abs(ry))));
    dt = phi / n;

    x[0] = xc + ROUND(rx * cos(theta));
    y[0] = yc + ROUND(ry * sin(theta));

    for (i = 1, m = 0; i < n; i++) {
	xx = xc + ROUND(rx * cos(theta + i * dt));
	yy = yc + ROUND(ry * sin(theta + i * dt));
	if (xx != x[m] || yy != y[m]) {
	    x[++m] = xx;
	    y[  m] = yy;
	}
    }

    if (flag) {	/* pie slice */
	x[++m] = xc;
	y[  m] = yc;
    }

    pixmap_fill_polygon(pixmap, pixel, m + 1, x, y);

    return;
}

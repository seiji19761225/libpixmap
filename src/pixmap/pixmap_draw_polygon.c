/*
 * pixmap_draw_polygon.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_draw_polygon.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "pixmap_internal.h"

/*======================================================================*/
void pixmap_draw_polygon(pixmap_t *pixmap, pixel_t pixel,
			 int n, int *x, int *y)
{				/* draw a polygon.                      */
    int i, j;

    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);
    assert(x != NULL);
    assert(y != NULL);

    for (j = n - 1, i = 0; i < n; j = i++)
	pixmap_draw_line(pixmap, pixel, x[i], y[i], x[j], y[j]);

    return;
}

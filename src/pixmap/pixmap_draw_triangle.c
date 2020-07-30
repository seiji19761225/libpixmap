/*
 * pixmap_draw_triangle.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_draw_triangle.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "pixmap_internal.h"

/*======================================================================*/
void pixmap_draw_triangle(pixmap_t *pixmap, pixel_t pixel,
			  int x0, int y0, int x1, int y1, int x2, int y2)
{				/* draw a triangle.                     */
    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);

    pixmap_draw_line(pixmap, pixel, x0, y0, x1, y1);
    pixmap_draw_line(pixmap, pixel, x1, y1, x2, y2);
    pixmap_draw_line(pixmap, pixel, x2, y2, x0, y0);

    return;
}

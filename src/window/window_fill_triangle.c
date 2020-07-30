/*
 * window_fill_triangle.c
 * (c)2014-2015 Seiji Nishimura
 * $Id: window_fill_triangle.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_fill_triangle(window_t *window, pixel_t pixel,
			  int x1, int y1, int x2, int y2, int x3, int y3)
{				/* draw a filled triangle.              */
    assert(window     != NULL);
    assert(window->be != NULL);

    pixmap_fill_triangle(&window->pixmap, pixel,
				x1, y1, x2, y2, x3, y3);

    return;
}

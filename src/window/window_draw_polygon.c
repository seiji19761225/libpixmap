/*
 * window_draw_polygon.c
 * (c)2014-2015 Seiji Nishimura
 * $Id: window_draw_polygon.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_draw_polygon(window_t *window, pixel_t pixel, int n, int *x, int *y)
{				/* draw a polygon.                      */
    assert(window     != NULL);
    assert(window->be != NULL);
    assert(x != NULL);
    assert(y != NULL);

    pixmap_draw_polygon(&window->pixmap, pixel, n, x, y);

    return;
}

/*
 * window_draw_line.c
 * (c)2014-2015 Seiji Nishimura
 * $Id: window_draw_line.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_draw_line(window_t *window, pixel_t pixel, int xs, int ys,
						       int xe, int ye)
{				/* draw a line from (xs,ys) to (xe,ye). */
    assert(window     != NULL);
    assert(window->be != NULL);

    pixmap_draw_line(&window->pixmap, pixel, xs, ys, xe, ye);

    return;
}

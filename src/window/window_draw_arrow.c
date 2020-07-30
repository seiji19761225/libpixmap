/*
 * window_draw_arrow.c
 * (c)2014-2015 Seiji Nishimura
 * $Id: window_draw_arrow.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_draw_arrow(window_t *window, pixel_t pixel, bool dual, bool sharp,
			int type, int width, int length, int xs, int ys, int xe, int ye)
{				/* draw an arrow.                       */
    assert(window     != NULL);
    assert(window->be != NULL);

    pixmap_draw_arrow(&window->pixmap, pixel, dual, sharp,
			type, width, length, xs, ys, xe, ye);

    return;
}

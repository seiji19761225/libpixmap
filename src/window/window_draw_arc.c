/*
 * window_draw_arc.c
 * (c)2014-2015 Seiji Nishimura
 * $Id: window_draw_arc.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_draw_arc(window_t *window, pixel_t pixel, int xc, int yc,
						      int rx, int ry, double theta, double phi)
{				/* draw an arc.                         */
    assert(window     != NULL);
    assert(window->be != NULL);

    pixmap_draw_arc(&window->pixmap, pixel, xc, yc, rx, ry, theta, phi);

    return;
}

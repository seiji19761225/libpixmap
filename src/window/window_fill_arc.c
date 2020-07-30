/*
 * window_fill_arc.c
 * (c)2014-2015 Seiji Nishimura
 * $Id: window_fill_arc.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_fill_arc(window_t *window, pixel_t pixel,
				bool mode, int xc, int yc,
					   int rx, int ry, double theta, double phi)
{				/* draw a filled arc.                   */
    assert(window     != NULL);
    assert(window->be != NULL);

    pixmap_fill_arc(&window->pixmap, pixel, mode,
				xc, yc, rx, ry, theta, phi);

    return;
}

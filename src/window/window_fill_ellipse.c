/*
 * window_fill_ellipse.c
 * (c)2014-2015 Seiji Nishimura
 * $Id: window_fill_ellipse.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_fill_ellipse(window_t *window, pixel_t pixel, int xc, int yc,
							  int rx, int ry)
{				/* draw a filled ellipse.               */
    assert(window     != NULL);
    assert(window->be != NULL);

    pixmap_fill_ellipse(&window->pixmap, pixel, xc, yc, rx, ry);

    return;
}

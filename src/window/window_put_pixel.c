/*
 * window_put_pixel.c
 * (c)2014-2015 Seiji Nishimura
 * $Id: window_put_pixel.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_put_pixel(window_t *window, pixel_t pixel, int x, int y)
{				/* put pixel at (x,y) on an window.     */
    assert(window     != NULL);
    assert(window->be != NULL);

    pixmap_put_pixel(&window->pixmap, pixel, x, y);

    return;
}

/*
 * window_draw_string.c
 * (c)2014-2015 Seiji Nishimura
 * $Id: window_draw_string.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_draw_string(window_t *window, pixel_t pixel, int x, int y, const char *str)
{				/* draw a string.                       */
    assert(window     != NULL);
    assert(window->be != NULL);
    assert(str != NULL);

    pixmap_draw_string(&window->pixmap, pixel, x, y, str);

    return;
}

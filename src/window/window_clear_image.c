/*
 * window_clear_image.c
 * (c)2014-2015 Seiji Nishimura
 * $Id: window_clear_image.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_clear_image(window_t *window, pixel_t pixel)
{				/* clear entire image of an window.     */
    assert(window     != NULL);
    assert(window->be != NULL);

    pixmap_clear_image(&window->pixmap, pixel);

    return;
}

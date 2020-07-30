/*
 * window_update_image.c
 * (c)2014-2015 Seiji Nishimura
 * $Id: window_update_image.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_update_image(window_t *window)
{				/* update entire image on an window.    */
    assert(window     != NULL);
    assert(window->be != NULL);

    _window_be_update_image(window->be, &window->pixmap,
				0, 0, window->pixmap.width, window->pixmap.height);

    return;
}

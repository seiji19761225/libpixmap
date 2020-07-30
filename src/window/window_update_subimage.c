/*
 * window_update_subimage.c
 * (c)2004-2009,2011-2015 Seiji Nishimura
 * $Id: window_update_subimage.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_update_subimage(window_t *window, int x, int y, int width, int height)
{				/* update subimage on an window.        */
    assert(window     != NULL);
    assert(window->be != NULL);

    _window_be_update_image(window->be, &window->pixmap, x, y, width, height);

    return;
}

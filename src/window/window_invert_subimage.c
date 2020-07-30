/*
 * window_invert_subimage.c
 * (c)2014-2015 Seiji Nishimura
 * $Id: window_invert_subimage.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_invert_subimage(window_t *window, int x, int y, int width, int height)
{				/* invert subimage of an window.        */
    assert(window     != NULL);
    assert(window->be != NULL);

    pixmap_invert_subimage(&window->pixmap, x, y, width, height);

    return;
}

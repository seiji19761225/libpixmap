/*
 * window_get_size.c
 * (c)2014-2015 Seiji Nishimura
 * $Id: window_get_size.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_get_size(window_t *window, int *width, int *height)
{				/* get size information of an window.   */
    assert(window     != NULL);
    assert(window->be != NULL);
    assert(width  != NULL);
    assert(height != NULL);

    pixmap_get_size(&window->pixmap, width, height);

    return;
}

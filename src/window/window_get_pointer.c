/*
 * window_get_pointer.c
 * (c)2020 Seiji Nishimura
 * $Id: window_get_pointer.c,v 1.1.1.1 2020/07/29 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
pixel_t *window_get_pointer(window_t *window)
{				/* get pointer to the pixel buffer.     */
    assert(window     != NULL);
    assert(window->be != NULL);

    return pixmap_get_pointer(&window->pixmap);
}

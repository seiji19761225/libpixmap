/*
 * window_get_image.c
 * (c)2013-2015 Seiji Nishimura
 * $Id: window_get_image.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_get_image(window_t *window, pixmap_t *pixmap)
{				/* create pixmap of an window image.    */
    assert(pixmap     != NULL);
    assert(window     != NULL);
    assert(window->be != NULL);

    pixmap_create(pixmap, window->pixmap.width, window->pixmap.height);
    pixmap_copy_image(&window->pixmap, pixmap);

    return;
}

/*
 * window_put_image.c
 * (c)2013-2015 Seiji Nishimura
 * $Id: window_put_image.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_put_image(window_t *window, pixmap_t *pixmap)
{				/* copy a pixmap image onto an window.  */
    assert(pixmap     != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);
    assert(window     != NULL);
    assert(window->be != NULL);

    pixmap_copy_image(pixmap, &window->pixmap);

    return;
}

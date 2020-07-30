/*
 * window_put_subimage.c
 * (c)2013-2015 Seiji Nishimura
 * $Id: window_put_subimage.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_put_subimage(window_t *window, int wx, int wy,
			 pixmap_t *pixmap, int px, int py, int width, int height)
{				/* copy a pixmap subimage onto an window.*/
    assert(pixmap     != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);
    assert(window     != NULL);
    assert(window->be != NULL);

    pixmap_copy_subimage(pixmap, px, py,
		&window->pixmap, wx, wy, width, height);

    return;
}

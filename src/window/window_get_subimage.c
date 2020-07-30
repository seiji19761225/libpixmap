/*
 * window_get_subimage.c
 * (c)2013-2015 Seiji Nishimura
 * $Id: window_get_subimage.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_get_subimage(window_t *window, int x    , int y,
			 pixmap_t *pixmap, int width, int height)
{				/* create pixmap of a window subimage.  */
    assert(pixmap     != NULL);
    assert(window     != NULL);
    assert(window->be != NULL);

    pixmap_create       (         pixmap,       width, height);
    pixmap_copy_subimage(&window->pixmap, x, y,
				  pixmap, 0, 0, width, height);

    return;
}

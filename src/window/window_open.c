/*
 * window_open.c
 * (c)2004-2009,2011-2015 Seiji Nishimura
 * $Id: window_open.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_open(window_t *window, int width, int height, const char *name)
{				/* open an window.                      */
    assert(window != NULL);
    assert(width  > 0);
    assert(height > 0);

    pixmap_create(&window->pixmap, width, height);
    window->be = _window_be_open(width, height, (name == NULL) ? "" : name);

    return;
}

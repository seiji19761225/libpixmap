/*
 * window_close.c
 * (c)2004-2009,2011-2015 Seiji Nishimura
 * $Id: window_close.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include <string.h>
#include "window_internal.h"

/*======================================================================*/
void window_close(window_t *window)
{				/* close an window.                     */
    assert(window     != NULL);
    assert(window->be != NULL);

    _window_be_close( window->be    );
    pixmap_destroy  (&window->pixmap);

    memset(window, 0x00, sizeof(window_t));

    return;
}

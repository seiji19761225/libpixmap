/*
 * window_rename.c
 * (c)2004-2009,2011-2015 Seiji Nishimura
 * $Id: window_rename.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_rename(window_t *window, const char *name)
{				/* rename an window.                    */
    assert(window     != NULL);
    assert(window->be != NULL);
    assert(name != NULL);

    _window_be_rename(window->be, (name == NULL) ? "" : name);

    return;
}

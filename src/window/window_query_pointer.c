/*
 * window_query_pointer.c
 * (c)2004-2009,2011-2015 Seiji Nishimura
 * $Id: window_query_pointer.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
int window_query_pointer(window_t *window, int *x, int *y)
{				/* query pointer position on the window.*/
    window_input_t input;

    assert(window     != NULL);
    assert(window->be != NULL);
    assert(x != NULL);
    assert(y != NULL);

    input = _window_be_query_pointer(window->be);
    *x    = input.x;
    *y    = input.y;

    return input.code;	/* EXIT_SUCCESS or EXIT_FAILURE */
}

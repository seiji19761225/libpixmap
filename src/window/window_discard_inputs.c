/*
 * window_discard_inputs.c
 * (c)2004-2009,2011-2015 Seiji Nishimura
 * $Id: window_discard_inputs.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_discard_inputs(window_t *window)
{				/* discard all user input events.       */
    window_input_t input;

    assert(window     != NULL);
    assert(window->be != NULL);

    do {
	input = _window_be_get_input(window->be, false);
    } while (input.device != WD_Null);

    return;
}

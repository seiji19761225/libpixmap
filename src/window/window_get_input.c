/*
 * window_get_input.c
 * (c)2004-2009,2011-2015 Seiji Nishimura
 * $Id: window_get_input.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
void window_get_input(window_t *window, bool sync,
		      int *device, int *code, int *x, int *y)
{				/* get a user input event.              */
    window_input_t input;

    assert(window     != NULL);
    assert(window->be != NULL);
    assert(device != NULL);
    assert(code   != NULL);
    assert(x      != NULL);
    assert(y      != NULL);

    input = _window_be_get_input(window->be, sync);

    if ((*device = input.device) == WD_Mouse) {
	*code = input.code;
	*x    = input.x;
	*y    = input.y;
    } else if (*device == WD_KeyBoard) {
	*code = input.code;
    }

    return;
}

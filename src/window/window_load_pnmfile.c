/*
 * window_load_pnmfile.c
 * (c)2004-2009,2011-2015 Seiji Nishimura
 * $Id: window_load_pnmfile.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include <stdlib.h>
#include "window_internal.h"

/*======================================================================*/
int window_load_pnmfile(window_t *window, const char *fname)
{				/* load a PNM image and open the window.*/
    assert(window != NULL);
    assert(fname  != NULL);

    if (pixmap_load_pnmfile(&window->pixmap, fname) == EXIT_FAILURE)
	return EXIT_FAILURE;

    window->be = _window_be_open(window->pixmap.width,
				 window->pixmap.height, fname);
    _window_be_update_image     (window->be, &window->pixmap, 0, 0,
				 window->pixmap.width, window->pixmap.height);

    return EXIT_SUCCESS;
}

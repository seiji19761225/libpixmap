/*
 * window_load_pnmfp.c
 * (c)2004-2009,2011-2015 Seiji Nishimura
 * $Id: window_load_pnmfp.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include <stdlib.h>
#include "window_internal.h"

/*======================================================================*/
int window_load_pnmfp(window_t *window, FILE *fp)
{				/* load a PNM image and open the window.*/
    assert(window != NULL);
    assert(fp     != NULL);

    if (pixmap_load_pnmfp(&window->pixmap, fp) == EXIT_FAILURE)
	return EXIT_FAILURE;

    window->be = _window_be_open(window->pixmap.width,
				 window->pixmap.height, "");
    _window_be_update_image     (window->be, &window->pixmap, 0, 0,
				 window->pixmap.width, window->pixmap.height);


    return EXIT_SUCCESS;
}

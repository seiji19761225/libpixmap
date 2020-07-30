/*
 * window_write_pnmfile.c
 * (c)2014-2015 Seiji Nishimura
 * $Id: window_write_pnmfile.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
int window_write_pnmfile(window_t *window, const char *fname)
{				/* write out an window as a PNM image.  */
    assert(window     != NULL);
    assert(window->be != NULL);
    assert(fname != NULL);

    return pixmap_write_pnmfile(&window->pixmap, fname);
}

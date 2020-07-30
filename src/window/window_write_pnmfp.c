/*
 * window_write_pnmfp.c
 * (c)2014-2015 Seiji Nishimura
 * $Id: window_write_pnmfp.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "window_internal.h"

/*======================================================================*/
int window_write_pnmfp(window_t *window, FILE *fp)
{				/* write out an window as a PNM image.  */
    assert(window     != NULL);
    assert(window->be != NULL);
    assert(fp != NULL);

    return pixmap_write_pnmfp(&window->pixmap, fp);
}

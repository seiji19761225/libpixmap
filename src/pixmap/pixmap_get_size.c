/*
 * pixmap_get_size.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_get_size.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "pixmap_internal.h"

/*======================================================================*/
void pixmap_get_size(pixmap_t *pixmap, int *width, int *height)
{				/* return size of a pixmap.             */
    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);
    assert(width  != NULL);
    assert(height != NULL);

    *width  = pixmap->width ;
    *height = pixmap->height;

    return;
}

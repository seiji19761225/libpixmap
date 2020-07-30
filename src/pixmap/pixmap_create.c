/*
 * pixmap_create.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_create.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include <stdlib.h>
#include "pixmap_internal.h"

/*======================================================================*/
void pixmap_create(pixmap_t *pixmap, int width, int height)
{				/* pixmap memory allocation.            */
    assert(pixmap != NULL);
    assert(width  > 0);
    assert(height > 0);

    if ((pixmap->data = (pixel_t *) calloc((size_t) width * height,
						sizeof(pixel_t))) == NULL)
	pixmap_abort(__func__);

    pixmap->width  = width ;
    pixmap->height = height;

    return;
}

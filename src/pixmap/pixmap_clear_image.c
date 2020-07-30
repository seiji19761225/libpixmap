/*
 * pixmap_clear_image.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_clear_image.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include <stddef.h>
#include "pixmap_internal.h"

/*======================================================================*/
void pixmap_clear_image(pixmap_t *pixmap, pixel_t pixel)
{				/* clear entire image of a pixmap.      */
    size_t i;

    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);

    for (i = 0; i < (size_t) pixmap->width * pixmap->height; i++)
	pixmap->data[i] = pixel;

    return;
}

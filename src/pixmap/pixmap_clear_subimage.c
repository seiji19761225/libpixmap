/*
 * pixmap_clear_subimage.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_clear_subimage.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include <stddef.h>
#include "pixmap_internal.h"

/*======================================================================*/
void pixmap_clear_subimage(pixmap_t *pixmap, pixel_t pixel,
			   int x, int y, int width, int height)
{				/* clear subimage of a pixmap.          */
    int i, j;

    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);

    if (width  < 0) { x += width ; width  *= -1; }
    if (height < 0) { y += height; height *= -1; }

    for (j = MAX(0, y); j < MIN(pixmap->height, y + height); j++)
	for (i = MAX(0, x); i < MIN(pixmap->width, x + width); i++)
	    pixmap->data[(size_t) j * pixmap->width + i] = pixel;

    return;
}

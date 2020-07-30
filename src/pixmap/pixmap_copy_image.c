/*
 * pixmap_copy_image.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_copy_image.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "pixmap_internal.h"

/*======================================================================*/
void pixmap_copy_image(pixmap_t *src, pixmap_t *dst)
{				/* copy entire image of src to dst.     */
    int i, j, width, height;
    pixel_t pixel;

    assert(src       != NULL);
    assert(src->data != NULL);
    assert(src->width  > 0);
    assert(src->height > 0);
    assert(dst       != NULL);
    assert(dst->data != NULL);
    assert(dst->width  > 0);
    assert(dst->height > 0);

    width  = MIN(src->width , dst->width );
    height = MIN(src->height, dst->height);

    for (j = 0; j < height; j++)
	for (i = 0; i < width; i++)
	    dst->data[(size_t) j * dst->width + i] =
		src->data[(size_t) j * src->width + i];

    return;
}

/*
 * pixmap_copy_subimage.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_copy_subimage.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "pixmap_internal.h"

/*======================================================================*/
void pixmap_copy_subimage(pixmap_t *src, int src_x, int src_y,
			  pixmap_t *dst, int dst_x, int dst_y, int width, int height)
{				/* copy subimage of src to dst.         */
    int i, j, k, l;

    assert(src       != NULL);
    assert(src->data != NULL);
    assert(src->width  > 0);
    assert(src->height > 0);
    assert(dst       != NULL);
    assert(dst->data != NULL);
    assert(dst->width  > 0);
    assert(dst->height > 0);

    if (width  < 0) { src_x += width ; dst_x += width ; width  *= -1; }
    if (height < 0) { src_y += height; dst_y += height; height *= -1; }

    for (j = MAX(0, src_y); j < MIN(src->height, src_y + height); j++)
	if ((l = dst_y - src_y + j) >= 0 &&
	     l < dst->height)
	    for (i = MAX(0, src_x); i < MIN(src->width, src_x + width); i++)
		if ((k = dst_x - src_x + i) >= 0 &&
		     k < dst->width)
		    dst->data[(size_t) l * dst->width + k] =
			src->data[(size_t) j * dst->width + i];

    return;
}

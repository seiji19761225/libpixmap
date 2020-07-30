/*
 * pixmap_invert_image.c
 * (c)2013-2015 Seiji Nishimura
 * $Id: pixmap_invert_image.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include <stddef.h>
#include "pixmap_internal.h"

/*======================================================================*/
void pixmap_invert_image(pixmap_t *pixmap)
#if 0
{				/* invert entire image of a pixmap.     */
    size_t i;

    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);

    for (i = 0; i < (size_t) pixmap->width * pixmap->height; i++) {
	pixmap->data[i].r = 0xff - pixel.r;
	pixmap->data[i].g = 0xff - pixel.g;
	pixmap->data[i].b = 0xff - pixel.b;
    }

    return;
}
#else				/*......................................*/
{				/* invert entire image of a pixmap.     */
    size_t i;

    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);

    for (i = 0; i < (size_t) pixmap->width * pixmap->height; i++) {
	pixmap->data[i].r ^= 0xff;
	pixmap->data[i].g ^= 0xff;
	pixmap->data[i].b ^= 0xff;
    }

    return;
}
#endif

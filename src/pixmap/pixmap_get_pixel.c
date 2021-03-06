/*
 * pixmap_get_pixel.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_get_pixel.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include <stddef.h>
#include "pixmap_internal.h"

/*======================================================================*/
void pixmap_get_pixel(pixmap_t *pixmap, pixel_t *pixel, int x, int y)
{				/* get a pixel at (x, y) on a pixmap.   */
    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);
    assert(pixel != NULL);

    if (x >= 0 && x < pixmap->width &&
	y >= 0 && y < pixmap->height) {
	*pixel = pixmap->data[(size_t) y * pixmap->width + x];
    } else {
	*pixel = pixel_set_rgb(0x00, 0x00, 0x00);	/* black */
    }

    return;
}

/*
 * pixmap_blend_image.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_blend_image.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "pixmap_internal.h"

/*======================================================================*/
void pixmap_blend_image(double alpha, pixmap_t *pm1, pixmap_t *pm2)
{				/* blend two pixmaps (=alpha bending).  */
    int i, j, width, height;
    pixel_t px1, px2;

    assert(pm1       != NULL);
    assert(pm1->data != NULL);
    assert(pm1->width  > 0);
    assert(pm1->height > 0);
    assert(pm2       != NULL);
    assert(pm2->data != NULL);
    assert(pm2->width  > 0);
    assert(pm2->height > 0);

    width  = MIN(pm1->width , pm2->width );
    height = MIN(pm1->height, pm2->height);

    for (j = 0; j < height; j++)
	for (i = 0; i < width; i++) {
	    px1 = pm1->data[(size_t) j * pm1->width + i];
	    px2 = pm2->data[(size_t) j * pm2->width + i];
	    pm2->data[(size_t) j * pm2->width + i] =
				pixel_blend(alpha, px1, px2);
	}

    return;
}

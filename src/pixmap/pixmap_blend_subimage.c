/*
 * pixmap_blend_subimage.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_blend_subimage.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "pixmap_internal.h"

/*======================================================================*/
void pixmap_blend_subimage(double alpha, pixmap_t *pm1, int pm1_x, int pm1_y,
					 pixmap_t *pm2, int pm2_x, int pm2_y, int width, int height)
{				/* blend subimage of pm1 to pm2.        */
    int i, j, k, l;
    pixel_t px1, px2;

    assert(pm1       != NULL);
    assert(pm1->data != NULL);
    assert(pm1->width  > 0);
    assert(pm1->height > 0);
    assert(pm2       != NULL);
    assert(pm2->data != NULL);
    assert(pm2->width  > 0);
    assert(pm2->height > 0);

    if (width  < 0) { pm1_x += width ; pm2_x += width ; width  *= -1; }
    if (height < 0) { pm1_y += height; pm2_y += height; height *= -1; }

    for (j = MAX(0, pm1_y); j < MIN(pm1->height, pm1_y + height); j++)
	if ((l = pm2_y - pm1_y + j) >= 0 &&
	     l < pm2->height)
	    for (i = MAX(0, pm1_x); i < MIN(pm1->width, pm1_x + width); i++)
		if ((k = pm2_x - pm1_x + i) >= 0 &&
		     k < pm2->height) {
		    px1 = pm1->data[(size_t) j * pm1->width + i];
		    px2 = pm2->data[(size_t) l * pm2->width + k];
		    pm2->data[(size_t) l * pm2->width + k] =
					pixel_blend(alpha, px1, px2);
		}

    return;
}

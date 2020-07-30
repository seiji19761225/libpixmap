/*
 * pixel_blend.c
 * (c)2013-2015 Seiji Nishimura
 * $Id: pixel_blend.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "pixmap_internal.h"

/*======================================================================*/
pixel_t pixel_blend(double alpha, pixel_t p, pixel_t q)
{				/* blend two pixels(=alpha blending).   */
    if (alpha >= 1.0)
	return p;

    if (alpha >  0.0) {
	q.r = ROUND(alpha * p.r + (1.0 - alpha) * q.r);
	q.g = ROUND(alpha * p.g + (1.0 - alpha) * q.g);
	q.b = ROUND(alpha * p.b + (1.0 - alpha) * q.b);
    }

    return q;
}

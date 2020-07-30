/*
 * pixel_invert.c
 * (c)2013-2015 Seiji Nishimura
 * $Id: pixel_invert.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include "pixmap_internal.h"

/*======================================================================*/
pixel_t pixel_invert(pixel_t pixel)
#if 0
{				/* invert a pixel value.                */
    pixel.r = 0xff - pixel.r;
    pixel.g = 0xff - pixel.g;
    pixel.b = 0xff - pixel.b;

    return pixel;
}
#else				/*......................................*/
{				/* invert a pixel value.                */
    pixel.r ^= 0xff;
    pixel.g ^= 0xff;
    pixel.b ^= 0xff;

    return pixel;
}
#endif

/*
 * pixmap_draw_line.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_draw_line.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include <stdlib.h>
#include "pixmap_internal.h"

/* clipping code */
#define LEFT	(0x01<<0)
#define RIGHT	(0x01<<1)
#define BOTTOM	(0x01<<2)
#define TOP	(0x01<<3)

/* internal functions */
static int  _pixmap_line_clip_code (pixmap_t *, int    , int);
static bool _pixmap_line_clip_point(pixmap_t *, int    , int *, int *, int, int, int, int);
static void _pixmap_draw_line      (pixmap_t *, pixel_t, int  , int  , int, int);

/*======================================================================*/
void pixmap_draw_line(pixmap_t *pixmap, pixel_t pixel, int xs, int ys, int xe, int ye)
{				/* draw line from (xs, ys) to (xe, ye). */
    int code_s, code_e;

    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);

    code_s = _pixmap_line_clip_code(pixmap, xs, ys);	// for (xs, ys)
    code_e = _pixmap_line_clip_code(pixmap, xe, ye);	// for (xe, ye)

    if ((code_s & code_e) ||
	(code_s && !_pixmap_line_clip_point(pixmap, code_s, &xs, &ys, xs, ys, xe, ye)) ||
	(code_e && !_pixmap_line_clip_point(pixmap, code_e, &xe, &ye, xs, ys, xe, ye)))
	return;

    _pixmap_draw_line(pixmap, pixel, xs, ys, xe, ye);

    return;
}

/*----------------------------------------------------------------------*/
static int _pixmap_line_clip_code(pixmap_t *pixmap, int x, int y)
{
    int code = 0x00;

    if (x <  0             ) code |= LEFT  ;
    if (x >= pixmap->width ) code |= RIGHT ;
    if (y <  0             ) code |= BOTTOM;
    if (y >= pixmap->height) code |= TOP   ;

    return code;
}

/*----------------------------------------------------------------------*/
static bool _pixmap_line_clip_point(pixmap_t *pixmap, int code,
					int *x, int *y, int xs, int ys, int xe, int ye)
{
    xe -= xs; ye -= ys;

    if (code & LEFT) {
	int z = ys - xs * ye / xe;
	if (z >= 0 && z < pixmap->height) {
	    *x = 0; *y = z;
	    return true;
	}
    }

    if (code & RIGHT) {
	int z = ys + (pixmap->width  - xs - 1) * ye / xe;
	if (z >= 0 && z < pixmap->height) {
	    *x = pixmap->width - 1; *y = z;
	    return true;
	}
    }

    if (code & BOTTOM) {
	int z = xs - ys * xe / ye;
	if (z >= 0 && z < pixmap->width) {
	    *x = z; *y = 0;
	    return true;
	}
    }

    if (code & TOP) {
	int z = xs + (pixmap->height - ys - 1) * xe / ye;
	if (z >= 0 && z < pixmap->width) {
	    *x = z; *y = pixmap->height - 1;
	    return true;
	}
    }

    return false;
}

/*----------------------------------------------------------------------*/
static void _pixmap_draw_line(pixmap_t *pixmap, pixel_t pixel, int xs, int ys, int xe, int ye)
{				/* draw line with Bresenham's algorithm.*/
    int dx, dy, ss, step;

    dx = abs(xe - xs); dy = abs(ye - ys);

    if (dx > dy) {
	if (xs > xe) {
	    step = (ys > ye) ? 1 : -1;
	    ss = xs; xs = xe; xe = ss; ys = ye;
	} else {
	    step = (ys < ye) ? 1 : -1;
	}
	pixmap->data[(size_t) ys * pixmap->width + xs] = pixel;
	ss = dx >> 0x01;
	while (++xs <= xe) {
	    if ((ss -= dy) < 0) {
		ss += dx; ys += step;
	    }
	    pixmap->data[(size_t) ys * pixmap->width + xs] = pixel;
	}
    } else {
	if (ys > ye) {
	    step = (xs > xe) ? 1 : -1;
	    ss = ys; ys = ye; ye = ss; xs = xe;
	} else {
	    step = (xs < xe) ? 1 : -1;
	}
	pixmap->data[(size_t) ys * pixmap->width + xs] = pixel;
	ss = dy >> 0x01;
	while (++ys <= ye) {
	    if ((ss -= dx) < 0) {
		ss += dy; xs += step;
	    }
	    pixmap->data[(size_t) ys * pixmap->width + xs] = pixel;
	}
    }

    return;
}

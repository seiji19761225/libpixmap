/*
 * pixmap_internal.h: pixmap library
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_internal.h,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#ifndef __PIXMAP_INTERNAL__
#define __PIXMAP_INTERNAL__

#include "pixmap.h"

/* for draw_arc, and fill_arc */
#define ARC_SAMPLING_FACTOR	(0x01<<2)
#define ARC_SAMPLING_LIMIT	(0x01<<12)

/* macro functions -----------------------------------------------------*/

#define NMEMB(ary)	(sizeof(ary)/sizeof(ary[0]))
#define ROUND(x)	((int) ((x)+(((x)>=0.0)?(+0.5):(-0.5))))
#define MIN(x,y)	(((x)<(y))?(x):(y))
#define MAX(x,y)	(((x)>(y))?(x):(y))

/* internal error handler */
#define pixmap_abort(msg)	_pixmap_abort(msg,__FILE__,__LINE__)

/* prototypes ----------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

void _pixmap_abort(const char *, const char *, const int);

#ifdef __cplusplus
}
#endif

#endif

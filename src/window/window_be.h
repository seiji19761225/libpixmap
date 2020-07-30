/*
 * window_be.h: low-level window system backend
 * (c)2004-2009,2011-2015 Seiji Nishimura
 * $Id: window_be.h,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#ifndef __WINDOW_BE_H__
#define __WINDOW_BE_H__

#include "window.h"

/* data type for _window_be_get_input ----------------------------------*/
typedef struct {
    int device, code, x, y;
} window_input_t;

/* prototypes ----------------------------------------------------------*/
#ifdef __WINDOW_BE_INTERNAL__
#define  WINDOW_BE_API
#else
#define  WINDOW_BE_API	extern
typedef void *window_be_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif

WINDOW_BE_API window_be_t    _window_be_open         (int, int, const char *);
WINDOW_BE_API void           _window_be_close        (window_be_t);
WINDOW_BE_API void           _window_be_update_image (window_be_t, pixmap_t *, int, int, int, int);
WINDOW_BE_API void           _window_be_rename       (window_be_t, const char *);
WINDOW_BE_API window_input_t _window_be_get_input    (window_be_t, bool);
WINDOW_BE_API window_input_t _window_be_query_pointer(window_be_t);

#ifdef __cplusplus
}
#endif

#undef WINDOW_BE_API
#endif

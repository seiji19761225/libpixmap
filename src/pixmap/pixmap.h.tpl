/*
 * pixmap.h: pixmap library
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap.h.tpl,v 1.1.1.4 2020/07/29 00:00:00 seiji Exp seiji $
 */

#ifndef __PIXMAP_H__
#define __PIXMAP_H__

#include <stdio.h>
#include <stdbool.h>

#define SIZEOF_PIXEL_T	__PIXEL_SZ__	/* == sizeof(pixel_t) */
#define FONT_WIDTH	__FONT_WID__	/* font size          */
#define FONT_HEIGHT	__FONT_HGT__

#if (SIZEOF_PIXEL_T != 3) && (SIZEOF_PIXEL_T != 4)
#error Wrong definition of SIZEOF_PIXEL_T.
#endif

/* arrow head types */
#define AH_TYPE0	0x00
#define AH_TYPE1	0x01
#define AH_TYPE2	0x02
#define AH_TYPE3	0x03
#define AH_TYPE4	0x04
#define AH_TYPE5	0x05
#define AH_TYPE6	0x06
#define AH_TYPE7	0x07

/* data types ----------------------------------------------------------*/

typedef struct {	/* pixel  */
#if        SIZEOF_PIXEL_T == 4
    unsigned char pad;	/* padding element */
#endif
    unsigned char r, g, b;
} pixel_t;

typedef struct {	/* pixmap */
    int width, height;
    pixel_t *data;
} pixmap_t;

/* macro functions -----------------------------------------------------*/

/* pixel manipulation */
#define pixel_get_r(p)		((int) (p).r)
#define pixel_get_g(p)		((int) (p).g)
#define pixel_get_b(p)		((int) (p).b)
#if        SIZEOF_PIXEL_T == 4
#define pixel_set_rgb(r,g,b)	((pixel_t) {0x00,r,g,b})
#else	/* SIZEOF_PIXEL_T == 3 */
#define pixel_set_rgb(r,g,b)	((pixel_t) {     r,g,b})
#endif

/* pixmap manipulation */
#define pixmap_get_pointer(p)	((p)->data)

/* prototypes ----------------------------------------------------------*/

#ifdef __PIXMAP_INTERNAL__
#define  PIXMAP_API
#else
#define  PIXMAP_API	extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

PIXMAP_API pixel_t pixel_blend           (double, pixel_t, pixel_t);
PIXMAP_API pixel_t pixel_invert          (pixel_t);
PIXMAP_API pixel_t pixel_set_named_color (const char *);

PIXMAP_API void    pixmap_create         (pixmap_t *, int, int);
PIXMAP_API void    pixmap_destroy        (pixmap_t *);
PIXMAP_API void    pixmap_blend_image    (double, pixmap_t *, pixmap_t *);
PIXMAP_API void    pixmap_blend_subimage (double, pixmap_t *, int, int, pixmap_t *, int, int, int, int);
PIXMAP_API void    pixmap_clear_image    (pixmap_t *, pixel_t);
PIXMAP_API void    pixmap_clear_subimage (pixmap_t *, pixel_t  , int , int  , int, int);
PIXMAP_API void    pixmap_copy_image     (pixmap_t *, pixmap_t *);
PIXMAP_API void    pixmap_copy_subimage  (pixmap_t *, int, int , pixmap_t  *, int, int, int, int);
PIXMAP_API void    pixmap_draw_arc       (pixmap_t *, pixel_t  , int , int  , int, int, double, double);
PIXMAP_API void    pixmap_draw_arrow     (pixmap_t *, pixel_t  , bool, bool , int, int, int, int, int, int, int);
PIXMAP_API void    pixmap_draw_ellipse   (pixmap_t *, pixel_t  , int , int  , int, int);
PIXMAP_API void    pixmap_draw_line      (pixmap_t *, pixel_t  , int , int  , int, int);
PIXMAP_API void    pixmap_draw_polygon   (pixmap_t *, pixel_t  , int , int *, int *);
PIXMAP_API void    pixmap_draw_triangle  (pixmap_t *, pixel_t  , int , int  , int, int, int, int);
PIXMAP_API void    pixmap_draw_string    (pixmap_t *, pixel_t  , int , int  , const char *);
PIXMAP_API void    pixmap_fill_arc       (pixmap_t *, pixel_t  , bool, int  , int, int, int, double, double);
PIXMAP_API void    pixmap_fill_ellipse   (pixmap_t *, pixel_t  , int , int  , int, int);
PIXMAP_API void    pixmap_fill_polygon   (pixmap_t *, pixel_t  , int , int *, int *);
PIXMAP_API void    pixmap_fill_triangle  (pixmap_t *, pixel_t  , int , int  , int, int, int, int);
PIXMAP_API void    pixmap_get_pixel      (pixmap_t *, pixel_t *, int , int);
PIXMAP_API void    pixmap_get_size       (pixmap_t *, int *, int *);
PIXMAP_API void    pixmap_put_pixel      (pixmap_t *, pixel_t  , int , int);
PIXMAP_API void    pixmap_invert_image   (pixmap_t *);
PIXMAP_API void    pixmap_invert_subimage(pixmap_t *, int, int , int , int);
PIXMAP_API int     pixmap_load_pnmfile   (pixmap_t *, const char *);
PIXMAP_API int     pixmap_load_pnmfp     (pixmap_t *, FILE *);
PIXMAP_API int     pixmap_write_pnmfile  (pixmap_t *, const char *);
PIXMAP_API int     pixmap_write_pnmfp    (pixmap_t *, FILE *);

#ifdef __cplusplus
}
#endif

#undef PIXMAP_API
#endif

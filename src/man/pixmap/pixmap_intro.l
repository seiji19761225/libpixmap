.\" $Id: pixmap_intro.l,v 1.1.1.6 2020/07/29 00:00:00 seiji Exp seiji $
.TH pixmap_intro l

.SH NAME
.B libpixmap
\- a portable pixmap library.

.SH SYNTAX
#include <libpixmap/pixmap.h>

.SH DESCRIPTION
The 
.B libpixmap
is a simple and portable pixmap library which provides 24bit full color graphics functionality.

Following API functions are provided through the
.B pixmap.h
header file:

.B pixel_blend
\- blend two pixels (=alpha blending).
.br
.B pixel_get_r, pixel_get_g, pixel_get_b
\- get the R,G,B value of a pixel.
.br
.B pixel_invert
\- invert the R,G,B value of a pixel.
.br
.B pixel_set_named_color
\- specify a pixel value by name.
.br
.B pixel_set_rgb
\- specify a pixel value in RGB format.
.br
.B pixmap_blend_image
\- blend two pixmaps (=alpha blending).
.br
.B pixmap_blend_subimage
\- blend subimages of two pixmaps (=alpha blending).
.br
.B pixmap_clear_image
\- clear entire image of a pixmap.
.br
.B pixmap_clear_subimage
\- clear subimage of a pixmap.
.br
.B pixmap_copy_image
\- copy entire image of a pixmap.
.br
.B pixmap_copy_subimage
\- copy subimage of a pixmap.
.br
.B pixmap_create
\- create a pixmap.
.br
.B pixmap_destroy
\- destroy a pixmap.
.br
.B pixmap_draw_arc
\- draw an arc.
.br
.B pixmap_draw_arrow
\- draw an arrow.
.br
.B pixmap_draw_ellipse
\- draw an ellipse.
.br
.B pixmap_draw_line
\- draw a line.
.br
.B pixmap_draw_polygon
\- draw a polygon.
.br
.B pixmap_draw_string
\-  draw a string.
.br
.B pixmap_fill_arc
\- draw a filled arc (pie slice or chord).
.br
.B pixmap_fill_ellipse
\- draw a filled ellipse.
.br
.B pixmap_fill_polygon
\- draw a filled polygon.
.br
.B pixmap_fill_triangle
\- draw a filled triangle.
.br
.B pixmap_get_pixel
\- get a pixel information.
.br
.B pixmap_get_pointer
\- get pointer to the pixel buffer of a pixmap.
.br
.B pixmap_get_size
\- get the size information of a pixmap.
.br
.B pixmap_invert_image
\- invert entire image of a pixmap.
.br
.B pixmap_invert_subimage
\- invert subimage of a pixmap.
.br
.B pixmap_put_pixel
\- put a pixel (=draw a point).
.br
.B pixmap_load_pnmfp, pixmap_load_pnmfile
\- load a PNM image and create the pixmap data.
.br
.B pixmap_write_pnmfp, pixmap_write_pnmfile
\- write out a pixmap in PNM image format.

.SH STRUCTURES
The
.B libpixmap
provides:

typedef struct {        // pixel
.br
#if SIZEOF_PIXEL_T == 4
    unsigned char pad;  // padding element
.br
#endif
    unsigned char r, g, b;
.br
} pixel_t;

typedef struct {        // pixmap
    int width, height;
    pixel_t *data;
.br
} pixmap_t;

These data structures are defined in the
.B pixmap.h
header file.
The padding element is included in a pixel data (=pixel_t) only if the library is configured to use 4byte pixel data. (The default is 4byte pixel data. The alternatve choice is 3byte pixel data.)
.br
A pixmap data (=pixmap_t) shold be created with a libpixmap function (e.g.
.BR pixmap_create ,
.BR pixmap_load_pnmfp ,
and
.BR pixmap_load_pnmfile
) and destroyed with the
.B pixmap_destroy
function.
All members of pixmap_t are READ ONLY - you should NOT modify any member of pixmap_t directly.

.SH SEE ALSO
.BR palette_intro (l),
.BR window_intro (l)

.SH COPYRIGHT
 (c)2010-2015 Seiji Nishimura, All rights reserved.

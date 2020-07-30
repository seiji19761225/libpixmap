.\" $Id: window_intro.l,v 1.1.1.5 2020/07/29 00:00:00 seiji Exp seiji $
.TH window_intro l

.SH NAME
.B window
\- window system interface module for libpixmap.

.SH SYNTAX
#include <libpixmap/window.h>

.SH DESCRIPTION
This module provides a portable window system interface for libpixmap.

Following API functions are provided through the
.B window.h
header file:

.B window_clear_image
\- clear entire image of an window.
.br
.B window_clear_subimage
\- clear subimage of an window.
.br
.B window_close
\- close an window.
.br
.B window_discard_inputs
\- discard all user input events.
.br
.B window_draw_arc
\- draw an arc.
.br
.B window_draw_arrow
\- draw an arrow.
.br
.B window_draw_ellipse
\- draw an ellipse.
.br
.B window_draw_line
\- draw a line.
.br
.B window_draw_polygon
\- draw a polygon.
.br
.B window_draw_string
\- draw a string.
.br
.B window_fill_arc
\- draw a filled arc.
.br
.B window_fill_ellipse
\- draw a filled ellipse.
.br
.B window_fill_polygon
\- draw a filled polygon.
.br
.B window_fill_triangle
\- draw a filled triangle.
.br
.B window_get_image
\- dump entire image of an window and create the pixmap data.
.br
.B window_get_input
\- get a user input event.
.br
.B window_get_pixel
\- get a pixel information.
.br
.B window_get_pointer
\- get pointer to the pixel buffer of an window.
.br
.B window_get_size
\- get the size information of an window.
.br
.B window_get_subimage
\- dump an window subimage and create the pixmap data.
.br
.B window_invert_image
\- invert entire image of an window.
.br
.B window_invert_subimage
\- invert subimage of an window.
.br
.B window_load_pnmfp, window_load_pnmfile
\- load a PNM image file and open the window.
.br
.B window_open
\- open an window.
.br
.B window_put_image
\- copy entire image of a pixmap onto an window.
.br
.B window_put_pixel
\- put a pixel (=draw a point).
.br
.B window_put_subimage
\- copy subimage of a pixmap onto an window.
.br
.B window_query_pointer
\- query mouse pointer position on the window.
.br
.B window_rename
\- rename an window.
.br
.B window_update_image
\- update entire image on an window.
.br
.B window_update_subimage
\- update subimage on an window.
.br
.B window_write_pnmfp, window_write_pnmfile
\- write out an window in PNM image format.

.SH STRUCTURES
The
.B libpixmap
window system interface module provides:

typedef struct {        // graphics window
    pixmap_t pixmap;    // internal pixmap data
    void *be;           // hook to the system dependent components
.br
} window_t;

This data structure (=window_t) is defined in the
.B window.h
header file.
The pixmap data type (=pixmap_t) is defined in the
.B pixmap.h
header file.
.br
An window (=window_t) shold be created with a libpixmap function (e.g.
.BR window_create ,
.BR window_load_pnmfp ,
and
.BR window_load_pnmfile
) and destroyed with the
.B window_destroy
function.
All members of window_t are READ ONLY - you should NOT modify any member of window_t directly.

.SH SEE ALSO
.BR palette_intro (l),
.BR pixmap_intro (l)

.SH COPYRIGHT
 (c)2010-2015 Seiji Nishimura, All rights reserved.

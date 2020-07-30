.\" $Id: window_fill_polygon.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_fill_polygon l

.SH NAME
.B window_fill_polygon
\- draw a filled polygon.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_fill_polygon
(window_t *\fIwindow\fP, pixel_t \fIpixel\fP, int \fIn\fP, int *\fIx\fP, int *\fIy\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIpixel\fP
Specifies the pixel value of the color.
.IP \fIn\fP
Specifies the number of the vertices of the polygon.
.IP \fIx\fP[],\ \fIy\fP[]
Specify the x and y coordinates of the vertices of the polygon.

.SH DESCRIPTION
The
.B window_fill_polygon
function draws a polygon filled with the specified pixel color using concave polygon scan conversion algorithm.
The number of the vertices should be a positive integer.

.SH SEE ALSO
.BR window_intro (l),
.BR pixmap_fill_polygon (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

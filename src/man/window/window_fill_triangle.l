.\" $Id: window_fill_triangle.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_fill_triangle l

.SH NAME
.B window_fill_triangle
\- draw a filled triangle.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_fill_triangle
(window_t *\fIwindow\fP, pixel_t \fIpixel\fP, int \fIx0\fP, int \fIy0\fP, int \fIx1\fP, int \fIy1\fP, int \fIx2\fP, int \fIy2\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIpixel\fP
Specifies the pixel value of the color.
.IP \fIx0\fP,\ \fIy0\fP
.br
.ns
.IP \fIx1\fP,\ \fIy1\fP
.br
.ns
.IP \fIx2\fP,\ \fIy2\fP
Specify the x and y coordinates of the three vertices of the triangle.

.SH DESCRIPTION
The
.B window_fill_triangle
function draws a triangle filled with the specified pixel color.

.SH SEE ALSO
.BR window_intro (l),
.BR pixmap_fill_triangle (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

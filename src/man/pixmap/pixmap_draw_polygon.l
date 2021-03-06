.\" $Id: pixmap_draw_polygon.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_draw_polygon l

.SH NAME
.B pixmap_draw_polygon
\- draw a polygon.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_draw_polygon
(pixmap_t *\fIpixmap\fP, pixel_t \fIpixel\fP, int \fIn\fP, int *\fIx\fP, int *\fIy\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data.
.IP \fIpixel\fP
Specifies the pixel value of the color.
.IP \fIn\fP
Specifies the number of the vertices of the polygon (> 0).
.IP \fIx\fP[],\ \fIy\fP[]
Specify the x and y coordinates of the vertices of the polygon.

.SH DESCRIPTION
The
.B pixmap_draw_polygon
function draws a polygon.
The number of the vertices should be a positive integer.

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_draw_line (l),
.BR pixmap_put_pixel (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

.\" $Id: pixmap_draw_line.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_draw_line l

.SH NAME
.B pixmap_draw_line
\- draw a line.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_draw_line
(pixmap_t *\fIpixmap\fP, pixel_t \fIpixel\fP, int \fIxs\fP, int \fIys\fP, int \fIxe\fP, int \fIye\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data.
.IP \fIpixel\fP
Specifies the pixel value of the color.
.IP \fIxs\fP,\ \fIys\fP
.br
.ns
.IP \fIxe\fP,\ \fIye\fP
Specify the x and y coordinates of the start and end of the line.

.SH DESCRIPTION
The
.B pixmap_draw_line
function draws a line from  (\fIxs\fP, \fIys\fP) to  (\fIxe\fP, \fIye\fP).

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_put_pixel (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

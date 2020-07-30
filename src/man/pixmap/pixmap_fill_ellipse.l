.\" $Id: pixmap_fill_ellipse.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_fill_ellipse l

.SH NAME
.B pixmap_fill_ellipse
\- draw a filled ellipse.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_fill_ellipse
(pixmap_t *\fIpixmap\fP, pixel_t \fIpixel\fP, int \fIxc\fP, int \fIyc\fP, int \fIrx\fP, int \fIry\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data.
.IP \fIpixel\fP
Specifies the pixel value of the color.
.IP \fIxc\fP,\ \fIyc\fP
Specify the x and y coordinates of the center of the ellipse.
.IP \fIrx\fP,\ \fIry\fP
Specify radiuces for x and y of the ellipse.

.SH DESCRIPTION
The
.B pixmap_fill_ellipse
function draws a single circle or ellipse filled with the specified pixel color.

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_draw_ellipse (l),
.BR pixmap_put_pixel (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

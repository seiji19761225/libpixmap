.\" $Id: pixmap_put_pixel.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_put_pixel l

.SH NAME
.B pixmap_put_pixel
\- put a pixel (=draw a point).

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_put_pixel
(pixmap_t *\fIpixmap\fP, pixel_t \fIpixel\fP, int \fIx\fP, int \fIy\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data.
.IP \fIpixel\fP
Specifies the pixel value of the color.
.IP \fIx\fP,\ \fIy\fP
Specify the x and y coordinates of the point.

.SH DESCRIPTION
The
.B pixmap_put_pixel
function function overwrites a pixel located at (\fIx\fP, \fIy\fP) on the specified pixmap with the specified pixel.

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_get_pixel (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

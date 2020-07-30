.\" $Id: pixmap_get_pixel.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_get_pixel l

.SH NAME
.B pixmap_get_pixel
\- get a pixel information.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_get_pixel
(pixmap_t *\fIpixmap\fP, pixel_t *\fIpixel\fP, int \fIx\fP, int \fIy\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data.
.IP \fIpixel\fP
Specifies a pixel_t variable, to which the the pixel value is returned.
.IP \fIx\fP,\ \fIy\fP
Specify the x and y coordinates of the pixel.

.SH DESCRIPTION
The
.B pixmap_get_pixel
function returns the specified pixel on the pixmap.

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_put_pixel (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

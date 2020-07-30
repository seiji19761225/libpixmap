.\" $Id: pixmap_clear_image.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_clear_image l

.SH NAME
.B pixmap_clear_image
\- clear entire image a pixmap.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_clear_image
(pixmap_t *\fIpixmap\fP, pixel_t \fIpixel\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data.
.IP \fIpixel\fP
Specifies the pixel value of the color.

.SH DESCRIPTION
The
.B pixmap_clear_image
function clears entire area (=image) of the pixmap with the specified pixel color.

.B pixmap_clear_image
(pixmap, pixel);
is the same as follow:
.br
.B pixmap_clear_subimage
(pixmap, pixel, 0, 0,
.br
	pixmap->width, pixmap->height);

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_clear_subimage (l),
.BR pixmap_put_pixel (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

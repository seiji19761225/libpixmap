.\" $Id: pixmap_invert_image.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_invert_image l

.SH NAME
.B pixmap_invert_image
\- invert entire image of a pixmap.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_invert_image
(pixmap_t *\fIpixmap\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data.

.SH DESCRIPTION
The
.B pixmap_invert_image
function inverts the entire area (=image) of the pixmap.

.B pixmap_invert_image
(pixmap);
is the same as follow:
.br
.B pixmap_invert_subimage
(pixmap, 0, 0, pixmap->width, pixmap->height);

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_get_pixel (l),
.BR pixmap_put_pixel (l),
.BR pixmap_invert_subimage (l),
.BR pixel_invert (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

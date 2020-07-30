.\" $Id: pixmap_invert_subimage.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_invert_subimage l

.SH NAME
.B pixmap_invert_subimage
\- invert subimage of a pixmap.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_invert_subimage
(pixmap_t *\fIpixmap\fP, int \fIx\fP, int \fIy\fP, int \fIwidth\fP, int \fIheight\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data.
.IP \fIx\fP,\ \fIy\fP
Specify the x and y coordinates of the left-top corner of the subimage.
.IP \fIwidth\fP,\ \fIheight\fP
Specify the width and height, which are the subimage's dimensions.

.SH DESCRIPTION
The
.B pixmap_invert_subimage
function inverts the specified area of the pixmap.

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_invert_image (l),
.BR pixmap_get_pixel (l),
.BR pixmap_put_pixel (l),
.BR pixel_invert (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

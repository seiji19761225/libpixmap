.\" $Id: pixmap_clear_subimage.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_clear_subimage l

.SH NAME
.B pixmap_clear_subimage
\- clear subimage of a pixmap.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_clear_subimage
(pixmap_t *\fIpixmap\fP, pixel_t \fIpixel\fP, int \fIxs\fP, int \fIys\fP, int \fIwidth\fP, int \fIheight\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data.
.IP \fIpixel\fP
Specifies the pixel value of the color.
.IP \fIxs\fP,\ \fIys\fP
Specify the x and y coordinates of the left-top corner of the subimage.
.IP \fIwidth\fP,\ \fIheight\fP
Specify the width and height, which are the subimage's dimensions.

.SH DESCRIPTION
The
.B pixmap_clear_subimage
function clears the specified area (=subimage) of the pixmap with the specified pixel color.

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_fill_polygon (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

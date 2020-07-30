.\" $Id: pixmap_copy_subimage.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_copy_subimage l

.SH NAME
.B pixmap_copy_subimage
\- copy subimage of a pixmap.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_copy_subimage
(pixmap_t *\fIsrc\fP, int \fIsrc_x\fP, int \fIsrc_y\fP, pixmap_t *\fIdst\fP, int \fIdst_x\fP, int \fIdst_y\fP, int \fIwidth\fP, int \fIheight\fP);

.SH ARGUMENTS
.IP \fIsrc\fP
Specifies the source pixmap data.
.IP \fIsrc_x\fP,\ \fIsrc_y\fP
Specify the x and y coordinates of the left-top corner of the subimage in the source pixmap.
.IP \fIdst\fP
Specifies the destination pixmap data.
.IP \fIdst_x\fP,\ \fIdst_y\fP
Specify the x and y coordinates of the left-top corner of the subimage in the destination pixmap.
.IP \fIwidth\fP,\ \fIheight\fP
Specify the width and height, which are the subimage's dimensions.

.SH DESCRIPTION
The
.B pixmap_copy_subimage
function copies the specified area (=subimage) of the source pixmap to the destination pixmap.

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_copy_image (l),
.BR pixmap_get_pixel (l),
.BR pixmap_put_pixel (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

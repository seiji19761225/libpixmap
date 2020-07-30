.\" $Id: pixmap_blend_subimage.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_blend_subimage l

.SH NAME
.B pixmap_blend_subimage
\- blend subimages of two pixmaps (=alpha blending).

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_blend_subimage
(double \fIalpha\fP, pixmap_t \fIp\fP, int \fIx1\fP, int \fIy1\fP, pixmap_t \fIq\fP, int \fIx2\fP, int \fIy2\fP, int \fIwidth\fP, int \fIheight\fP);

.SH ARGUMENTS
.IP \fIalpha\fP
Specify the alpha value (0.0 <= alpha <= 1.0).
.IP \fIp\fP,\ \fIq\fP
Specify the pixmaps to be blended.
.IP \fIx1\fP,\ \fIy1\fP
Specify the x and y coordinates of the left-top corner of the subimage in the pixmap \fIp\fP.
.IP \fIx2\fP,\ \fIy2\fP
Specify the x and y coordinates of the left-top corner of the subimage in the pixmap \fIq\fP.
.IP \fIwidth\fP,\ \fIheight\fP
Specify the width and height, which are the subimage's dimensions.

.SH DESCRIPTION
The
.B pixmap_blend_subimage
function blends subimages of the specified two pixmaps.
The blending function is:
.br
	\fIq\fP(i,j) := \fIalpha\fP * \fIp\fP(k,l) + (1.0 - \fIalpha\fP) * \fIq\fP(i,j);
where i=x2,x2+1,...,x2+\fIwidth\fP-1 j=y2,y2+1,...,y2+\fIheight\fP-1 k=i-x2+x1 and l=j-y2+y1.

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_blend_image (l),
.BR pixel_blend (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

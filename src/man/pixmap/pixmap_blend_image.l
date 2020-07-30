.\" $Id: pixmap_blend_image.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_blend_image l

.SH NAME
.B pixmap_blend_image
\- blend two pixmaps (=alpha blending).

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_blend_image
(double \fIalpha\fP, pixmap_t \fIp\fP, pixmap_t \fIq\fP);

.SH ARGUMENTS
.IP \fIalpha\fP
Specify the alpha value (0.0 <= alpha <= 1.0).
.IP \fIp\fP,\ \fIq\fP
Specify the pixmaps to be blended.

.SH DESCRIPTION
The
.B pixmap_blend_image
function blends the specified two pixmaps.
The blending function is:
.br
	\fIq\fP(i,j) := \fIalpha\fP * \fIp\fP(i,j) + (1.0 - \fIalpha\fP) * \fIq\fP(i,j);
where i=0,1,..,width-1 and j=0,1,...,height-1.

.B pixmap_blend_image
(pixmap1, pixmap2);
is the same as follow:
.br
.B pixmap_blend_subimage
(pixmap1, 0, 0, pixmap2, 0, 0,
.br
	MIN(pixmap1->width , pixmap2->width ),
.br
	MIN(pixmap1->height, pixmap2->height));

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_blend_subimage (l),
.BR pixel_blend (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

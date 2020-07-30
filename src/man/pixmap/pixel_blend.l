.\" $Id: pixel_blend.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixel_blend l

.SH NAME
.B pixel_blend
\- blend two pixels (=alpha blending).

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
pixel_t
.B pixel_blend
(double \fIalpha\fP, pixel_t \fIp\fP, pixel_t \fIq\fP);

.SH ARGUMENTS
.IP \fIalpha\fP
Specify the alpha value (0.0 <= alpha <= 1.0).
.IP \fIp\fP,\ \fIq\fP
Specify the pixel values to be blended.

.SH DESCRIPTION
The
.B pixel_blend
function returns the blended pixel value of the specified two pixels.
The blending function is:
.br
	\fIalpha\fP * \fIp\fP + (1.0 - \fIalpha\fP) * \fIq\fP

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_blend_image (l),
.BR pixmap_blend_subimage (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

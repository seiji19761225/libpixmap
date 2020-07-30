.\" $Id: pixel_invert.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixel_invert l

.SH NAME
.B pixel_invert
\- invert a pixel value.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
pixel_t
.B pixel_invert
(pixel_t \fIpixel\fP);

.SH ARGUMENTS
.IP \fIpixel\fP
Specify the pixel.

.SH DESCRIPTION
The
.B pixel_invert
function returns inverted pixel value of the specified pixel.

.SH SEE ALSO
.BR pixmap_intro (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

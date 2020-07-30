.\" $Id: window_clear_image.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_clear_image l

.SH NAME
.B window_clear_image
\- clear entire image of an window.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_clear_image
(window_t *\fIwindow\fP, pixel_t \fIpixel\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIpixel\fP
Specifies the pixel value of the color.

.SH DESCRIPTION
The
.B window_clear_image
function clears entire area (=image) of the window with the specified pixel color.

.SH SEE ALSO
.BR window_intro (l),
.BR pixmap_clear_image (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

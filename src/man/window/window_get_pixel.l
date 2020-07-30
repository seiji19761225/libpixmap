.\" $Id: window_get_pixel.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_get_pixel l

.SH NAME
.B window_get_pixel
\- get a pixel information.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_get_pixel
(window_t *\fIwindow\fP, pixel_t *\fIpixel\fP, int \fIx\fP, int \fIy\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIpixel\fP
Specifies a pixel_t variable, to which the the pixel value is returned.
.IP \fIx\fP,\ \fIy\fP
Specify the x and y coordinates of the pixel.

.SH DESCRIPTION
The
.B window_get_pixel
function returns the specified pixel on the window.

.SH SEE ALSO
.BR window_intro (l),
.BR window_put_pixel (l),
.BR pixmap_get_pixel (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

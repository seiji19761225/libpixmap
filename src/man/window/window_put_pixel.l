.\" $Id: window_put_pixel.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_put_pixel l

.SH NAME
.B window_put_pixel
\- put a pixel (=draw a point).

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_put_pixel
(window_t *\fIwindow\fP, pixel_t \fIpixel\fP, int \fIx\fP, int \fIy\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIpixel\fP
Specifies the pixel value of the color.
.IP \fIx\fP,\ \fIy\fP
Specify the x and y coordinates of the point.

.SH DESCRIPTION
The
.B window_put_pixel
function function overwrites a pixel located at (\fIx\fP, \fIy\fP) on the specified window with the specified pixel.

.SH SEE ALSO
.BR window_intro (l),
.BR pixmap_put_pixel (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

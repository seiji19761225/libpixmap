.\" $Id: window_draw_ellipse.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_draw_ellipse l

.SH NAME
.B window_draw_ellipse
\- draw an ellipse.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_draw_ellipse
(window_t *\fIwindow\fP, pixel_t \fIpixel\fP, int \fIxc\fP, int \fIyc\fP, int \fIrx\fP, int \fIry\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIpixel\fP
Specifies the pixel value of the color.
.IP \fIxc\fP,\ \fIyc\fP
Specify the x and y coordinates of the center of the ellipse.
.IP \fIrx\fP,\ \fIry\fP
Specify radiuces for x and y of the ellipse.

.SH DESCRIPTION
The
.B window_draw_ellipse
function draws a single circle or ellipse.

.SH SEE ALSO
.BR window_intro (l),
.BR pixmap_draw_ellipse (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

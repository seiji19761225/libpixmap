.\" $Id: window_draw_arc.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_draw_arc l

.SH NAME
.B window_draw_arc
\- draw an arc.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_draw_arc
(window_t *\fIwindow\fP, pixel_t \fIpixel\fP, int \fIxc\fP, int \fIyc\fP, int \fIrx\fP, int \fIry\fP, double \fItheta\fP, double \fIphi\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIpixel\fP
Specifies the pixel value of the color.
.IP \fIxc\fP,\ \fIyc\fP
Specify the x and y coordinates of the center of the arc.
.IP \fIrx\fP,\ \fIry\fP
Specify radiuces for x and y of the arc.
.IP \fItheta\fP
Specifies the start angle of the arc relative to the three-o'clock position from the center, in unit of radian.
.IP \fIphi\fP
Specifies the path and extent angle of the arc relative to the start of the arc, in units of radian.

.SH DESCRIPTION
The
.B window_draw_arc
function draws a single circular or elliptical arc.
Positive angles indicate clockwise motion, and negative angles indicate counterclockwise motion.
If the absolute magnitude of \fIphi\fP is greater than 2*PI, this function truncates it to 2*PI.

.SH SEE ALSO
.BR window_intro (l),
.BR window_draw_ellipse (l),
.BR pixmap_draw_arc (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

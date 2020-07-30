.\" $Id: pixmap_fill_arc.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_fill_arc l

.SH NAME
.B pixmap_fill_arc
\- draw a filled arc  (chord or pie slice).

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_fill_arc
(pixmap_t *\fIpixmap\fP, pixel_t \fIpixel\fP, bool \fIflag\fP, int \fIxc\fP, int \fIyc\fP, int \fIrx\fP, int \fIry\fP, double \fItheta\fP, double \fIphi\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data.
.IP \fIpixel\fP
Specifies the pixel value of the color.
.IP \fIflag\fP
Specifies filling mode; chord (=false) or pie slice (=true).
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
.B pixmap_fill_arc
function draws a circular or elliptical arc filled with the specified pixel color.
If true is specified for \fIflag\fP, the pie slice mode is used; otherwise, the chord mode is used.
Positive angles indicate clockwise motion, and negative angles indicate counterclockwise motion.
If the absolute magnitude of \fIphi\fP is greater than 2*PI, this function truncates it to 2*PI.

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_draw_arc (l),
.BR pixmap_draw_line (l),
.BR pixmap_fill_ellipse (l),
.BR pixmap_fill_triangle (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

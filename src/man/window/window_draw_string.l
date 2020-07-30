.\" $Id: window_draw_string.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_draw_string l

.SH NAME
.B window_draw_string
\- draw a string.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_draw_string
(window_t *\fIwindow\fP, pixel_t \fIpixel\fP, int \fIxs\fP, int \fIys\fP, const char *\fIstr\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIpixel\fP
Specifies the pixel value of the color.
.IP \fIxs\fP,\ \fIys\fP
Specify the x and y coordinates of the start  (left-top corner) of the string.
.IP \fIstr\fP
Specifies the string.

.SH DESCRIPTION
The
.B window_draw_string
function draws a string from  (\fIxs\fP, \fIys\fP).

.SH SEE ALSO
.BR window_intro (l),
.BR pixmap_draw_string (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

.\" $Id: pixmap_draw_string.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_draw_string l

.SH NAME
.B pixmap_draw_string
\- draw a string.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_draw_string
(pixmap_t *\fIpixmap\fP, pixel_t \fIpixel\fP, int \fIxs\fP, int \fIys\fP, const char *\fIstr\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data.
.IP \fIpixel\fP
Specifies the pixel value of the color.
.IP \fIxs\fP,\ \fIys\fP
Specify the x and y coordinates of the start  (left-top corner) of the string.
.IP \fIstr\fP
Specifies the string.

.SH DESCRIPTION
The
.B pixmap_draw_string
function draws a string from  (\fIxs\fP, \fIys\fP).

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_put_pixel (l)

.SH COPYRIGHT
(c)1995 Simon J. Gerraty.
.br
(c)2010-2015 Seiji Nishimura, All rights reserved.

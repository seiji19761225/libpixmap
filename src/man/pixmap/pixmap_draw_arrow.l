.\" $Id: pixmap_draw_arrow.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_draw_arrow l

.SH NAME
.B pixmap_draw_arrow
\- draw an arrow.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_draw_arrow
(pixmap_t *\fIpixmap\fP, pixel_t \fIpixel\fP, bool \fIdual\fP,  bool \fIsharp\fP, int \fItype\fP, int \fIwidth\fP, int \fIlength\fP, int \fIxs\fP, int \fIys\fP, int \fIxe\fP, int \fIye\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data.
.IP \fIpixel\fP
Specifies the pixel value of the color.
.IP \fIdual\fP
Specify single (=false) or dual (=true) head arrow.
.IP \fIsharp\fP
Specify normal (=false) or sharp (=true) arrow head.
.IP \fItype\fP
Specifies type of arrow head.
.IP \fIwidth\fP,\ \fIlength\fP
Specify width and length of the head.
.IP \fIxs\fP,\ \fIys\fP
.br
.ns
.IP \fIxe\fP,\ \fIye\fP
Specify the x and y coordinates of the start and end of the arrow.

.SH DESCRIPTION
The
.B pixmap_draw_arrow
function draws an arrow from  (\fIxs\fP, \fIys\fP) to  (\fIxe\fP, \fIye\fP).

.SH CONSTANTS
// arrow head type
.br
AH_TYPE0   0x00,	AH_TYPE1  0x01
.br
AH_TYPE2   0x02,	AH_TYPE3  0x03
.br
AH_TYPE4   0x04,	AH_TYPE5  0x05
.br
AH_TYPE6   0x06,	AH_TYPE7  0x07

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_draw_line (l),
.BR pixmap_fill_polygon (l),
.BR pixmap_fill_triangle (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

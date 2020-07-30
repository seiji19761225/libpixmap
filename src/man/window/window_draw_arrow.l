.\" $Id: window_draw_arrow.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_draw_arrow l

.SH NAME
.B window_draw_arrow
\- draw an arrow.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_draw_arrow
(window_t *\fIwindow\fP, pixel_t \fIpixel\fP,  bool \fIdual\fP,  bool \fIsharp\fP, int \fItype\fP, int \fIwidth\fP, int \fIlength\fP, int \fIxs\fP, int \fIys\fP, int \fIxe\fP, int \fIye\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
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
.B window_draw_arrow
function draws an arrow from  (\fIxs\fP, \fIys\fP) to  (\fIxe\fP, \fIye\fP).
The \fIshape\fP is the bitwise inclusive OR of the valid mask bits  (head type, head sharpness, and single/dual head). Its range is [0:AH_NTYPES).

.SH CONSTANTS
// head type
.br
AH_TYPE0   0x00,	AH_TYPE1  0x01
.br
AH_TYPE2   0x02,	AH_TYPE3  0x03
.br
AH_TYPE4   0x04,	AH_TYPE5  0x05
.br
AH_TYPE6   0x06,	AH_TYPE7  0x07

.SH SEE ALSO
.BR window_intro (l),
.BR pixmap_draw_arrow (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

.\" $Id: window_invert_subimage.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_invert_subimage l

.SH NAME
.B window_invert_subimage
\- invert subimage of an window.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_invert_subimage
(window_t *\fIwindow\fP, int \fIxs\fP, int \fIys\fP, int \fIwidth\fP, int \fIheight\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIxs\fP,\ \fIys\fP
Specify the x and y coordinates of the left-top corner of the box.
.IP \fIwidth\fP,\ \fIheight\fP
Specify width and height of the box.

.SH DESCRIPTION
The
.B window_invert_subimage
function inverts the specified area (=subimage) of the window.

.SH SEE ALSO
.BR window_intro (l),
.BR pixmap_invert_subimage (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

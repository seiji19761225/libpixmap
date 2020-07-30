.\" $Id: window_update_subimage.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_update_subimage l

.SH NAME
.B window_update_subimage
\- update subimage on an window.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_update_subimage
(window_t *\fIwindow\fP, int \fIx\fP, int \fIy\fP, int \fIwidth\fP, int \fIheight\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIx\fP,\ \fIy\fP
Specify the x and y coordinates of the left-top corner of the subimage.
.IP \fIwidth\fP,\ \fIheight\fP
Specify the width and height, which are the subimage's dimensions.

.SH DESCRIPTION
The
.B window_update_subimage
function updates the specified area of the window (=copies the subimage from the internal pixmap data).

.SH SEE ALSO
.BR window_intro (l),
.BR window_update_image (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

.\" $Id: window_put_subimage.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_put_subimage l

.SH NAME
.B window_put_subimage
\- copy subimage of a pixmap onto an window.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_put_subimage
(window_t *\fIwindow\fP, int \fIwx\fP, int \fIwy\fP, pixmap_t *\fIpixmap\fP, int \fIpx\fP, int \fIpy\fP, int \fIwidth\fP, int \fIheight\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIwx\fP,\ \fIwy\fP
Specify the x and y coordinates of the left-top corner of the subimage on the window.
.IP \fIpixmap\fP
Specifies the pixmap data.
.IP \fIpx\fP,\ \fIpy\fP
Specify the x and y coordinates of the left-top corner of the subimage in the pixmap.
.IP \fIwidth\fP,\ \fIheight\fP
Specify the width and height, which are the subimage's dimensions.

.SH DESCRIPTION
The
.B window_put_subimage
function copies subimage of the specified pixmap onto the specified window.

.SH SEE ALSO
.BR window_intro (l),
.BR window_get_image (l),
.BR window_get_subimage (l),
.BR window_put_image (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

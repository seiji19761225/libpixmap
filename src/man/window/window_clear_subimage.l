.\" $Id: window_clear_subimage.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_clear_subimage l

.SH NAME
.B window_clear_subimage
\- clear subimage of an window.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_clear_subimage
(window_t *\fIwindow\fP, pixel_t \fIpixel\fP, int \fIxs\fP, int \fIys\fP, int \fIwidth\fP, int \fIheight\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIpixel\fP
Specifies the pixel value of the color.
.IP \fIxs\fP,\ \fIys\fP
Specify the x and y coordinates of the left-top corner of the subimage.
.IP \fIwidth\fP,\ \fIheight\fP
Specify width and height of the subimage.

.SH DESCRIPTION
The
.B window_clear_subimage
function clears the specified area (=subimage) of the window with the specified pixel color.

.SH SEE ALSO
.BR window_intro (l),
.BR pixmap_clear_subimage (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

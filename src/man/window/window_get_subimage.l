.\" $Id: window_get_subimage.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_get_subimage l

.SH NAME
.B window_get_subimage
\- dump an window subimage and create the pixmap data.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_get_subimage
(window_t *\fIwindow\fP, int \fIx\fP, int \fIy\fP, pixmap_t *\fIpixmap\fP, int \fIwidth\fP, int \fIheight\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIpixmap\fP
Specifies the pixmap to be created.
.IP \fIx\fP,\ \fIy\fP
Specify the x and y coordinates of the left-top corner of the subimage in the window.
.IP \fIwidth\fP,\ \fIheight\fP
Specify the width and height, which are the subimage's dimensions.

.SH DESCRIPTION
The
.B window_get_subimage
function dumps subimage of an window and creates the pixmap data.

The created pixmap should be destroyed with the
.B pixmap_destroy
function to free the allocated memory space when it is no longer needed.

.SH SEE ALSO
.BR window_intro (l),
.BR window_get_image (l),
.BR window_put_image (l),
.BR window_put_subimage (l),
.BR pixmap_destroy (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

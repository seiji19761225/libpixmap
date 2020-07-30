.\" $Id: window_get_image.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_get_image l

.SH NAME
.B window_get_image
\- dump entire image of an window and create the pixmap data.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_get_image
(window_t *\fIwindow\fP, pixmap_t *\fIpixmap\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIpixmap\fP
Specifies the pixmap to be created.

.SH DESCRIPTION
The
.B window_get_image
function dumps entire image of an window and creates the pixmap data.

The created pixmap should be destroyed with the
.B pixmap_destroy
function to free the allocated memory space when it is no longer needed.

.SH SEE ALSO
.BR window_intro (l),
.BR window_get_subimage (l),
.BR window_put_image (l),
.BR window_put_subimage (l),
.BR pixmap_destroy (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

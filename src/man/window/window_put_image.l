.\" $Id: window_put_image.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_put_image l

.SH NAME
.B window_put_image
\- copy entire image of a pixmap onto an window.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_put_image
(window_t *\fIwindow\fP, pixmap_t *\fIpixmap\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIpixmap\fP
Specifies the pixmap data.

.SH DESCRIPTION
The
.B window_put_image
function copies entire image of the specified pixmap onto the specified window.

.SH SEE ALSO
.BR window_intro (l),
.BR window_get_image (l),
.BR window_get_subimage (l),
.BR window_put_subimage (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

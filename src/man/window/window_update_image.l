.\" $Id: window_update_image.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_update_image l

.SH NAME
.B window_update_image
\- update entire image on an window.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_update_image
(window_t *\fIwindow\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.

.SH DESCRIPTION
The
.B window_update_image
function updates entire area of the window (=copies entire image from the internal pixmap data).

.SH SEE ALSO
.BR window_intro (l),
.BR window_update_subimage (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

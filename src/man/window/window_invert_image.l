.\" $Id: window_invert_image.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_invert_image l

.SH NAME
.B window_invert_image
\- invert entire image of an window.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_invert_image
(window_t *\fIwindow\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.

.SH DESCRIPTION
The
.B window_invert_image
function inverts entire area (=image) of the window.

.SH SEE ALSO
.BR window_intro (l),
.BR pixmap_invert_image (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

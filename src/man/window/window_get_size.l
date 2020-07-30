.\" $Id: window_get_size.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_get_size l

.SH NAME
.B window_get_size
\- get the size information of an window.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_get_size
(window_t *\fIwindow\fP, int *\fIwidth\fP, int *\fIheight\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIwidth\fP,\ \fIheight\fP
Specify two integer variables, to which width and height of the window are returned.

.SH DESCRIPTION
The
.B window_get_size
function returns \fIwidth\fP and \fIheight\fP of the specified window, which are the window's dimensions.

.SH SEE ALSO
.BR window_intro (l),
.BR window_open (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

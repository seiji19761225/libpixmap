.\" $Id: window_close.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_close l

.SH NAME
.B window_close
\- close an window.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_close
(window_t *\fIwindow\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window to be closed.

.SH DESCRIPTION
The
.B window_close
function closes the specified window and destroys its internal pixmap data.
The \fIwindow\fP should never be referenced again after this call.

.SH SEE ALSO
.BR window_intro (l),
.BR window_open (l),
.BR pixmap_destroy (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

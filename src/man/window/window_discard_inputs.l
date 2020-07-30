.\" $Id: window_discard_inputs.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_discard_inputs l

.SH NAME
.B window_discard_inputs
\- discard all user input events.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_discard_inputs
(window_t *\fIwindow\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.

.SH DESCRIPTION
The
.B window_discard_inputs
function discards all user input events in the queue for the specified window.

.SH SEE ALSO
.BR window_intro (l),
.BR window_get_input (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

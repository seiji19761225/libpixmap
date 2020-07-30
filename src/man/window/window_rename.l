.\" $Id: window_rename.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_rename l

.SH NAME
.B window_rename
\- rename an window.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_rename
(window_t *\fIwindow\fP, const char *\fIname\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIname\fP
Specifies the new name of the window.

.SH DESCRIPTION
The
.B window_rename
function renames the specified window.

.SH SEE ALSO
.BR window_intro (l),
.BR window_open (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

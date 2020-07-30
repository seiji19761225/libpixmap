.\" $Id: window_get_pointer.l,v 1.1.1.1 2020/07/29 00:00:00 seiji Exp seiji $
.TH window_get_pointer l

.SH NAME
.B window_get_pointer
\- get pointer to the pixel buffer of an window.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
pixel_t *
.B window_get_pointer
(window_t *\fIwindow\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window data.

.SH DESCRIPTION
The
.B window_get_pointer
function returns pointer to the pixel buffer of the specified window.

.SH SEE ALSO
.BR window_intro (l),
.BR window_open (l)

.SH COPYRIGHT
(c)2010-2015,2020 Seiji Nishimura, All rights reserved.

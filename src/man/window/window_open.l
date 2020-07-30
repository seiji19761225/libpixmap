.\" $Id: window_open.l,v 1.1.1.5 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_open l

.SH NAME
.B window_open
\- open an window.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_open
(window_t *\fIwindow\fP, int \fIwidth\fP, int \fIheight\fP, const char *\fIname\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window to be opened.
.IP \fIwidth\fP,\ \fIheight\fP
Specify the width and height, which are the created window's dimensions.
.IP \fIname\fP
Specifies the name of the window.

.SH DESCRIPTION
The
.B window_open
function opens an window.
Its internal pixmap data is also created.
The function terminates execution of the user program if enough memory space is not left on the system.
The \fIwidth\fP and \fIheight\fP should be positive integers.

The opened window should be closed with the
.B window_close
function to free the allocated memory spaces when it is no longer needed.

.SH SEE ALSO
.BR window_intro (l),
.BR window_close (l),
.BR pixmap_create (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

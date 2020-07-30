.\" $Id: window_query_pointer.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_query_pointer l

.SH NAME
.B window_query_pointer
\- query mouse pointer position on the window.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
int
.B window_query_pointer
(window_t *\fIwindow\fP, int *\fIx\fP, int *\fIy\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIx\fP,\ \fIy\fP
Specify two integer variables, to which the x and y coordinates of the mouse pointer are returned.

.SH DESCRIPTION
The
.B window_query_pointer
function returns current position of the mouse pointer.

This function returns EXIT_SUCCESS if the position is successfully obtained; otherwise, EXIT_FAILURE is returned (=the mouse pointer is NOT on the screen on which the window is located).

.SH SEE ALSO
.BR window_intro (l),
.BR window_get_input (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

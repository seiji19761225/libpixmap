.\" $Id: window_get_input.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_get_input l

.SH NAME
.B window_get_input
\- get a user input event.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
void
.B window_get_input
(window_t *\fIwindow\fP, bool \fIsync\fP, int *\fIdevice\fP, int *\fIcode\fP, int *\fIx\fP, int *\fIy\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIsync\fP
Specifies the mode.
.IP \fIdevice\fP,\ \fIcode\fP,\ \fIx\fP,\ \fIy\fP
Specify four integer variables, to which the input device ID, code and position of the mouse pointer are returned.

.SH DESCRIPTION
The
.B window_get_input
function returns a user input event.
If true is specified for \fIsync\fP, synchronous mode is used  (wait for a user input event); otherwise, asynchronous mode is used  (no wait and return immediately).

If a keyboard input event is given, WD_KeyBoard is returned to \fIdevice\fP and the keycode is returned to \fIcode\fP (no return to \fIx\fP and \fIy\fP).
If a mouse input event is given, WD_Mouse is returned to \fIdevice\fP.
The input code and position of the mouse pointer are returned to \fIcode\fP, \fIx\fP and \fIy\fP respectively.
Otherwise, WD_Null is returned to \fIdevice\fP (for asynchronous mode only, and no return to \fIcode\fP, \fIx\fP and \fIy\fP).

.SH CONSTANTS
// device ID
.br
WD_Null       0,	WD_KeyBoard   1,	WD_Mouse      2
.br
// mouse input code
.br
WM_Motion     0,	WM_Button1    1,	WM_Button2    2,
.br
WM_Button3    3,	WM_WheelUp    4,	WM_WheelDown  5,
.br
WM_Drag       6,	WM_Release    7

.SH SEE ALSO
.BR window_intro (l),
.BR window_discard_inputs (l),
.BR window_query_pointer (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

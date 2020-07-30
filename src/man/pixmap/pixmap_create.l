.\" $Id: pixmap_create.l,v 1.1.1.5 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_create l

.SH NAME
.B pixmap_create
\- create a pixmap.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_create
(pixmap_t *\fIpixmap\fP, int \fIwidth\fP, int \fIheight\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data to be created.
.IP \fIwidth\fP,\ \fIheight\fP
Specify the width and height, which are the created pixmap's dimensions.

.SH DESCRIPTION
The
.B pixmap_create
function creates a pixmap data and initializes all pixels with black.
The function terminates execution of the user program if enough memory space is not left on the system.
The \fIwidth\fP and \fIheight\fP should be positive integers.

The created pixmap should be destroyed with the
.B pixmap_destroy
function to free the allocated memory space when it is no longer needed.

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_destroy (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

.\" $Id: pixmap_destroy.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_destroy l

.SH NAME
.B pixmap_destroy
\- destroy a pixmap.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_destroy
(pixmap_t *\fIpixmap\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data to be destroyed.

.SH DESCRIPTION
The
.B pixmap_destroy
function destroys the specified pixmap data.
The \fIpixmap\fP should never be referenced again after this call.

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_create (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

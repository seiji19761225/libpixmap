.\" $Id: pixmap_get_pointer.l,v 1.1.1.2 2020/07/29 00:00:00 seiji Exp seiji $
.TH pixmap_get_pointer l

.SH NAME
.B pixmap_get_pointer
\- get pointer to the pixel buffer of a pixmap.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
pixel_t *
.B pixmap_get_pointer
(pixmap_t *\fIpixmap\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data.

.SH DESCRIPTION
The
.B pixmap_get_pointer
function returns pointer to the pixel buffer of the specified pixmap.

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_create (l)

.SH COPYRIGHT
(c)2010-2015,2020 Seiji Nishimura, All rights reserved.

.\" $Id: pixmap_get_size.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_get_size l

.SH NAME
.B pixmap_get_size
\- get the size information of a pixmap.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_get_size
(pixmap_t *\fIpixmap\fP, int *\fIwidth\fP, int *\fIheight\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data.
.IP \fIwidth\fP,\ \fIheight\fP
Specify two integer variables, to which width and height of the pixmap are returned.

.SH DESCRIPTION
The
.B pixmap_get_size
function returns \fIwidth\fP and \fIheight\fP of the specified pixmap, which are the pixmap's dimensions.

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_create (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

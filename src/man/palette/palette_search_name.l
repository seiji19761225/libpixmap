.\" $Id: palette_search_name.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH palette_search_name l

.SH NAME
.B palette_search_name
\- search color palette name by ID.

.SH SYNTAX
#include <libpixmap/palette.h>
.HP
const char *
.B palette_search_name
(int *\fIid\fP);

.SH ARGUMENTS
.IP \fIid\fP
Specifies the color palette ID.

.SH DESCRIPTION
The
.B palette_search_name
function returns the color palette name specified with the \fIid\fP.
If the \fIid\fP is not appropriate, NULL is returned.
The range of the \fIid\fP is [0:PALETTE_NTYPES).

.SH SEE ALSO
.BR palette_intro (l),
.BR palette (l),
.BR palette_search_id (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

.\" $Id: palette_search_id.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH palette_search_id l

.SH NAME
.B palette_search_id
\- search color palette ID by name.

.SH SYNTAX
#include <libpixmap/palette.h>
.HP
int
.B palette_search_id
(const char *\fIname\fP);

.SH ARGUMENTS
.IP \fIname\fP
Specifies the color palette name.

.SH DESCRIPTION
The
.B palette_search_id
function returns the color palette ID specified with the \fIname\fP.
If the \fIname\fP is not appropriate, a negative integer is returned.
The range of the color palette ID is [0:PALETTE_NTYPES).

.SH SEE ALSO
.BR palette_intro (l),
.BR palette (l),
.BR palette_search_name (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

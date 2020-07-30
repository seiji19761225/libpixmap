.\" $Id: palette.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH palette l

.SH NAME
.B palette
\- color palette function.

.SH SYNTAX
#include <libpixmap/palette.h>
.HP
pixel_t
.B palette
(int \fIid\fP, double \fIdmin\fP, double \fIdmax\fP, double \fIdata\fP);

.SH ARGUMENTS
.IP \fIid\fP
Specifies the color palette ID.
.IP \fIdmin\fP,\ \fIdmax\fP
Specify the range of the numerical data.
.IP \fIdata\fP
Specifies the numerical data.

.SH DESCRIPTION
The
.B palette
function returns the pixel value of the color corresponding with the specified \fIdata\fP.
If the \fIid\fP is not appropriate, black pixel is returned.
The range of the \fIid\fP is [0:PALETTE_NTYPES).

.SH SEE ALSO
.BR palette_intro (l),
.BR palette_search_id (l),
.BR palette_search_name (l)
.br
EGGX/ProCALL - X11 Graphics Library since 1999 by Chisato Yamauchi.

.SH COPYRIGHT
(c)Chisato Yamauchi.
.br
(c)2010-2015 Seiji Nishimura, All rights reserved.

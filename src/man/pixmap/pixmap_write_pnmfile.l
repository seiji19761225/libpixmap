.\" $Id: pixmap_write_pnmfile.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_write_pnm l

.SH NAME
.B pixmap_write_pnmfp, pixmap_write_pnmfile
\- write out a pixmap in PNM image format.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
int
.B pixmap_write_pnmfp
(pixmap_t *\fIpixmap\fP, FILE *\fIfp\fP);
.HP
int
.B pixmap_write_pnmfile
(pixmap_t *\fIpixmap\fP, const char *\fIfname\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data.
.IP \fIfp\fP
Specifies the file pointer.
.IP \fIfname\fP
Specifies the file name.

.SH DESCRIPTION
The
.BR pixmap_write_pnmfp ,
.BR pixmap_write_pnmfile
functions write out the specified pixmap data in PNM image format.
EXIT_SUCCESS is returned if the PNM image could be written without any error; otherwise, EXIT_FAILURE is returned.

If "-" is specified as the file name, the PNM image is written to the standard output.

The PNM image type (PBM/PGM/PPM) is automatically determined with the suffix of \fIfname\fP and/or visual class of the \fIpixmap\fP image.

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_load_pnmfp (l),
.BR pixmap_load_pnmfile (l)
.br
libpnmrw - PBM/PGM/PPM read/write library by Jef Poskanzer.

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

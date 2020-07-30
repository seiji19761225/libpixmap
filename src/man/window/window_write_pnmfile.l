.\" $Id: window_write_pnmfile.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_write_pnm l

.SH NAME
.B window_write_pnmfp, window_write_pnmfile
\- write out an window in PNM image format.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
int
.B window_write_pnmfp
(window_t *\fIwindow\fP, FILE *\fIfp\fP);
.HP
int
.B window_write_pnmfile
(window_t *\fIwindow\fP, const char *\fIfname\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIfp\fP
Specifies the file pointer.
.IP \fIfname\fP
Specifies the file name.

.SH DESCRIPTION
The
.BR window_write_pnmfp ,
.BR window_write_pnmfile
functions write out the specified window in PNM image format.
EXIT_SUCCESS is returned if the PNM image could be written without any error; otherwise, EXIT_FAILURE is returned.

If "-" is specified as the file name, the PNM image is written to the standard output.

The PNM image type (PBM/PGM/PPM) is automatically determined with the suffix of \fIfname\fP and/or visual class of the \fIwindow\fP image.

.SH SEE ALSO
.BR window_intro (l),
.BR window_load_pnmfp (l),
.BR window_load_pnmfile (l),
.BR pixmap_write_pnmfp (l),
.BR pixmap_write_pnmfile (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

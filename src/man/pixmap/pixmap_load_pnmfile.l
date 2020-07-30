.\" $Id: pixmap_load_pnmfile.l,v 1.1.1.5 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_load_pnm l

.SH NAME
.B pixmap_load_pnmfp, pixmap_load_pnmfile
\- load a PNM image and create the pixmap data.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
int
.B pixmap_load_pnmfp
(pixmap_t *\fIpixmap\fP, FILE *\fIfp\fP);
.HP
int
.B pixmap_load_pnmfile
(pixmap_t *\fIpixmap\fP, const char *\fIfname\fP);

.SH ARGUMENTS
.IP \fIpixmap\fP
Specifies the pixmap data.
.IP \fIfp\fP
Specifies the file pointer of a PNM image.
.IP \fIfname\fP
Specifies the file name of a PNM image.

.SH DESCRIPTION
The
.BR pixmap_load_pnmfp ,
.BR pixmap_load_pnmfile
functions load a PNM image from the specified file and creates the pixmap data.
These functions terminate execution of the user program if enough memory space is not left on the system.
EXIT_SUCCESS is returned if the PNM image could be loaded without any error; otherwise, EXIT_FAILURE is returned.

The created pixmap should be destroyed with the
.B pixmap_destroy
function to free the allocated memory space when it is no longer needed.

If "-" is specified as the file name, the PNM image is loaded from the standard input.

The PNM image type (PBM/PGM/PPM) is automatically detected.

.SH EXAMPLE
Following code is an example to handle IO error:

if (pixmap_load_pnmfile(&pixmap, fname) == EXIT_FAILURE)
.br
    if (errno) {    /* system error      */
.br
        perror(fname);
.br
    } else {        /* file format error */
.br
        fprintf(stderr, "%s: Not a ppm, pgm, or pbm file\\n", fname);
.br
    }

.SH SEE ALSO
.BR errno (3),
.BR perror (3),
.BR pixmap_intro (l),
.BR pixmap_create (l),
.BR pixmap_destroy (l),
.BR pixmap_write_pnmfp (l),
.BR pixmap_write_pnmfile (l)
.br
libpnmrw - PBM/PGM/PPM read/write library by Jef Poskanzer.

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

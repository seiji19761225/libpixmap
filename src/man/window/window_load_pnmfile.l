.\" $Id: window_load_pnmfile.l,v 1.1.1.5 2015/01/14 00:00:00 seiji Exp seiji $
.TH window_load_pnm l

.SH NAME
.B window_load_pnmfp, window_load_pnmfile
\- load a PNM image and open the window.

.SH SYNTAX
#include <libpixmap/window.h>
.HP
int
.B window_load_pnmfp
(window_t *\fIwindow\fP, FILE *\fIfp\fP);
.HP
int
.B window_load_pnmfile
(window_t *\fIwindow\fP, const char *\fIfname\fP);

.SH ARGUMENTS
.IP \fIwindow\fP
Specifies the window.
.IP \fIfp\fP
Specifies the file pointer of a PNM image.
.IP \fIfname\fP
Specifies the file name of a PNM image.

.SH DESCRIPTION
The
.BR window_load_pnmfp ,
.BR window_load_pnmfile
functions load a PNM image from the specified file and open the window.
These functions terminate execution of the user program if enough memory space is not left on the system.
EXIT_SUCCESS is returned if the PNM image could be loaded without any error; otherwise, EXIT_FAILURE is returned.

The opened window should be closed with the
.B window_close
function to free the allocated memory spaces when it is no longer needed.

If "-" is specified as the file name, the PNM image is loaded from the standard input.

The PNM image type (PBM/PGM/PPM) is automatically detected.

.SH EXAMPLE
Following code is an example to handle IO error:

if (window_load_pnmfile(&window, fname) == EXIT_FAILURE)
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
.BR window_intro (l),
.BR window_open (l),
.BR window_close (l),
.BR window_write_pnmfp (l),
.BR window_write_pnmfile (l),
.BR pixmap_load_pnmfp (l),
.BR pixmap_load_pnmfile (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

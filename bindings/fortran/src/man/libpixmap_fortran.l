.\" $Id: libpixmap_fortran.l,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
.TH libpixmap_fortran l

.SH NAME
.B libpixmap_fortran
\- FORTRAN binding of libpixmap

.SH SYNTAX
USE libpixmap_core
.br
USE libpixmap_palette
.br
USE libpixmap_window

.SH DESCRIPTION
The
.B libpixmap_fortran
is FORTRAN binding of libpixmap library.
It is consisted of following three FORTRAN modules:
.br
.B libpixmap_core
\- core module (pixmap.h)
.br
.B libpixmap_palette
\- palette module (palette.h)
.br
.B libpixmap_window
\- window module (window.h)

The
.B libpixmap_window
module is optional.
It will be included in the library only when the libpixmap library is configured to include the window module.

Each function/subroutine has the same name and requires the same sequence of the arguments as the corresponding C/C++ API function.
Each constant parameter is also the same name as in C/C++.
.br
Note that FORTRAN bindings of the PNM image file I/O procedures (
.B pixmap_load_pnmfile, pixmap_write_pnmfile, window_load_pnmfile and window_write_pnmfile
) are defined as subroutines.
I/O status is returned if optional INTEGER argument istat is given.
Otherwise, a simple error message is printed out to stderr when I/O error happens.
.br
The
.B palette_search_name
function returns a CHARACTER(LEN=PALETTE_NAME_MAX_LENGTH) string.

All interfaces are implemented with FORTRAN2003's ISO_C_BINDING to directly call lower API functions written in C/C++.

.SH DATA TYPES
The
.B libpixmap_core
module provides
.B TYPE(pixel)
and
.B TYPE(pixmap)
data types, which is binded to
.B pixel_t
and
.B pixmap_t
data types in C/C++, respectively.

The
.B libpixmap_window
module provides
.B TYPE(window)
data type, which is binded to
.B window_t
data type in C/C++.

.SH SEE ALSO
.BR pixmap_intro (l),
.BR palette_intro (l),
.BR window_intro (l)

.SH COPYRIGHT
 (c)2013-2015 Seiji Nishimura, All rights reserved.

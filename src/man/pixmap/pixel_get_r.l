.\" $Id: pixel_get_r.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixel_get l

.SH NAME
.B pixel_get_r, pixel_get_g, pixel_get_b
\- get the R,G,B value of a pixel.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
unsigned char
.B pixel_get_r
(pixel_t \fIpixel\fP);
.HP
unsigned char
.B pixel_get_g
(pixel_t \fIpixel\fP);
.HP
unsigned char
.B pixel_get_b
(pixel_t \fIpixel\fP);

.SH ARGUMENTS
.IP \fIpixel\fP
Specify the pixel.

.SH DESCRIPTION
The
.B pixel_get_r, pixel_get_g, pixel_get_b
functions return the R,G,B value of the specified pixel, respectively.
These functions are implemented as macros in the
.B pixel.h
header file.

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixel_set_rgb (l),
.BR pixel_set_named_color (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

.\" $Id: pixel_set_rgb.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixel_set_rgb l

.SH NAME
.B pixel_set_rgb
\- specify a pixel value by RGB.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
pixel_t
.B pixel_set_rgb
(int \fIred\fP, int \fIgreen\fP, int \fIblue\fP);

.SH ARGUMENTS
.IP \fIred\fP,\ \fIgreen\fP,\ \fIblue\fP
Specify the RGB color.

.SH DESCRIPTION
The
.B pixel_set_rgb
function returns the pixel value of the specified RGB color.
This function is implemented as a macro in the
.B pixel.h
header file, which can be used in a "const" declaration sentence as follow:

const pixel_t black =
.B pixel_set_rgb
(0x00, 0x00, 0x00);

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixel_get_r (l),
.BR pixel_get_g (l),
.BR pixel_get_b (l),
.BR pixel_set_named_color (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

.\" $Id: pixel_set_named_color.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixel_set_named_color l

.SH NAME
.B pixel_set_named_color
\- specify a pixel value by name.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
pixel_t
.B pixel_set_named_color
(const char *\fIname\fP);

.SH ARGUMENTS
.IP \fIname\fP
Specifies the color name.

.SH DESCRIPTION
The
.B pixel_set_named_color
function returns the pixel value of the specified color name.
If the \fIname\fP is not appropriate, black pixel is returned.

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixel_get_r (l),
.BR pixel_get_g (l),
.BR pixel_get_b (l),
.BR pixel_set_rgb (l)
.br
.B /usr/X11R6/lib/rgb.txt
(X11 color name database file)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

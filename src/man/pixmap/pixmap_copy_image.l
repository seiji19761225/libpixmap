.\" $Id: pixmap_copy_image.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH pixmap_copy_image l

.SH NAME
.B pixmap_copy_image
\- copy entire image of a pixmap.

.SH SYNTAX
#include <libpixmap/pixmap.h>
.HP
void
.B pixmap_copy_image
(pixmap_t *\fIsrc\fP, pixmap_t *\fIdst\fP);

.SH ARGUMENTS
.IP \fIsrc\fP
Specifies the source pixmap data.
.IP \fIdst\fP
Specifies the destination pixmap data.

.SH DESCRIPTION
The
.B pixmap_copy_image
function copies the entire area (=image) of the source pixmap to the destination pixmap.

This function call

.B pixmap_copy_image
(pixmap1, pixmap2);
is the same as follow:
.br
.B pixmap_copy_subimage
(pixmap1, 0, 0, pixmap2, 0, 0,
.br
	MIN(pixmap1->width , pixmap2->width ),
.br
	MIN(pixmap1->height, pixmap2->height));

.SH SEE ALSO
.BR pixmap_intro (l),
.BR pixmap_get_pixel (l),
.BR pixmap_put_pixel (l),
.BR pixmap_copy_subimage (l)

.SH COPYRIGHT
(c)2010-2015 Seiji Nishimura, All rights reserved.

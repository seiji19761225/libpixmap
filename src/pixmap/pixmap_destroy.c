/*
 * pixmap_destroy.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_destroy.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "pixmap_internal.h"

/*======================================================================*/
void pixmap_destroy(pixmap_t *pixmap)
{				/* pixmap memory deallocation.          */
    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);

    free  (pixmap->data);
    memset(pixmap, 0x00, sizeof(pixmap_t));

    return;
}

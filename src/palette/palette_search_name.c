/*
 * palette_search_name.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: palette_search_name.c,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "palette_internal.h"

/*----------------------------------------------------------------------*/
const char *palette_search_name(int id)
{				/* search color palette name by ID.     */
    static const char *palette_name_tbl[] = {
    /* auto-generated from palette.h with tools/palette_names.pl.       */
#include "palette_names.h"
    };

    if (id < 0 || id >= NMEMB(palette_name_tbl))
	return NULL;

    return palette_name_tbl[id];
}

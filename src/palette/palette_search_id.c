/*
 * palette_search_id.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: palette_search_id.c,v 1.1.1.4 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "palette_internal.h"

typedef struct {
    char *name;
    int id;
} palette_id_t;

/* internal function */
static int cmp_palette_id_tbl(const void *, const void *);

/*----------------------------------------------------------------------*/
int palette_search_id(const char *name)
{				/* search color palette ID by name.     */
    palette_id_t *p, work;
    const palette_id_t palette_id_tbl[] = {
    /* auto-generated from palette.h with tools/palette_ids.pl.         */
#include "palette_ids.h"
    };

    assert(name != NULL);

    work.name = (char *) name;

    if ((p = bsearch(&work, palette_id_tbl,   NMEMB(palette_id_tbl),
		     sizeof(palette_id_tbl[0]), cmp_palette_id_tbl)) == NULL)
	return -1;		/* no match */

    return p->id;
}

/*......................................................................*/
static int cmp_palette_id_tbl(const void *p, const void *q)
{				/* compare function for bsearch         */
    return strcasecmp(((palette_id_t *) p)->name, 
		      ((palette_id_t *) q)->name);
}

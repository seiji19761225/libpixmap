/*
 * pixel_set_named_color.c
 * (c)2012-2015 Seiji Nishimura
 * $Id: pixel_set_named_color.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "pixmap_internal.h"

typedef struct {
    char *name;
    unsigned char r, g, b;
} named_color_t;

/* internal function */
static int cmp_named_color_tbl(const void *, const void *);

/*======================================================================*/
pixel_t pixel_set_named_color(const char *name)
{				/* specify a pixel value by name.       */
    int i;
    named_color_t *p, work;
    const pixel_t black = pixel_set_rgb(0x00, 0x00, 0x00);
    const named_color_t named_color_tbl[] = {
    /* automatically generated with tools/named_colors.pl.              */
#include "named_colors.h"
    };

    assert(name != NULL);

    work.name = (char *) name;

    if ((p = bsearch(&work, named_color_tbl,   NMEMB(named_color_tbl),
		     sizeof(named_color_tbl[0]), cmp_named_color_tbl)) == NULL) {
	if ((work.name = strdup(name)) == NULL)
	    pixmap_abort(__func__);
	for (i = 0; (work.name[i] = tolower(work.name[i])) != '\0'; i++);
	if (strcmp(name, work.name) == 0 ||
	    (p = bsearch(&work, named_color_tbl,   NMEMB(named_color_tbl),
			 sizeof(named_color_tbl[0]), cmp_named_color_tbl)) == NULL) {
	    free(work.name);
	    return black;
	}
	free(work.name);
    }

    return pixel_set_rgb(p->r, p->g, p->b);
}

/*----------------------------------------------------------------------*/
static int cmp_named_color_tbl(const void *p, const void *q)
{				/* compare function for bsearch         */
    return strcmp(((named_color_t *) p)->name,
		  ((named_color_t *) q)->name);
}

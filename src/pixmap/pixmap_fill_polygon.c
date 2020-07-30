/*
 * pixmap_fill_polygon.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_fill_polygon.c,v 1.1.1.3 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "pixmap_internal.h"

/* internal data types */
typedef struct {
    double x, y;
} point_t;

typedef struct {
    int i;
    double x, dx;
} edge_t;

typedef struct {
    int n, nact;
    point_t *pt;
    edge_t *active;
} polygon_t;

/* internal functions */
static void _pixmap_fill_polygon_concave(pixmap_t   *, pixel_t, int, point_t *);
static void _pixmap_fill_polygon_cdelete(polygon_t  *, int);
static void _pixmap_fill_polygon_cinsert(polygon_t  *, int    , int);
static void _pixmap_fill_polygon_sortidx(polygon_t  *, int *  , int, int);
static int  _pixmap_fill_polygon_cmpactv(const void *, const void *);

/*======================================================================*/
void pixmap_fill_polygon(pixmap_t *pixmap, pixel_t pixel,
			 int n, int *x, int *y)
{				/* draw a filled polygon.               */
    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);
    assert(x != NULL);
    assert(y != NULL);

    switch (n) {
    case (1):	/* point */
	pixmap_put_pixel(pixmap, pixel, x[0], y[0]);
	break;
    case (2):	/* line  */
	pixmap_draw_line(pixmap, pixel, x[0], y[0], x[1], y[1]);
	break;
    default:
	if (n > 0) {
	    int i;
	    point_t *p;
#ifdef DRAW_OUTLINE
	    pixmap_draw_polygon(pixmap, pixel, n, x, y);
#endif
	    if ((p = (point_t *) malloc(n * sizeof(point_t))) == NULL)
		pixmap_abort(__func__);
	    for (i = 0; i < n; i++) {
		p[i].x = x[i];
		p[i].y = y[i];
	    }
	    _pixmap_fill_polygon_concave(pixmap, pixel, n, p);
	    free(p);
	}
	break;
    }

    return;
}

/*======================================================================*/
/* internal functions                                                   */

/* Concave Polygon Scan Conversion by Paul Heckbert
 * from "Graphics Gems", Academic Press, 1990.
 */

/*----------------------------------------------------------------------*/
static void _pixmap_fill_polygon_concave(pixmap_t *pixmap, pixel_t pixel,
					 int nvert, point_t *point)
{
    int i, j, k, x, y, xl, xr, y0, y1, *ind;
    polygon_t pgn;
    struct {
	int x0, y0, x1, y1;
    } win;

    win.x0 = win.y0 = 0;
    win.x1 = pixmap->width  - 1;
    win.y1 = pixmap->height - 1;

    pgn.n  = nvert;
    pgn.pt = point;

    if ((ind        = (int    *) malloc(pgn.n * sizeof(int   ))) == NULL ||
	(pgn.active = (edge_t *) malloc(pgn.n * sizeof(edge_t))) == NULL)
	pixmap_abort(__func__);

    for (k = 0; k < pgn.n; k++)
	ind[k] = k;

    _pixmap_fill_polygon_sortidx(&pgn, ind, 0, pgn.n - 1);

    y0 = MAX(win.y0, pgn.pt[ind[0        ]].y);
    y1 = MIN(win.y1, pgn.pt[ind[pgn.n - 1]].y);

    k = pgn.nact = 0;
    for (y = y0; y <= y1; y++) {
	for (; k < pgn.n && (int) pgn.pt[ind[k]].y <= y; k++) {
	    i = ind[k];
	    j = (i > 0) ? i - 1 : pgn.n - 1;
	    if ((x = (int) pgn.pt[j].y) < y) {
		_pixmap_fill_polygon_cdelete(&pgn, j);
	    } else if (x != y) {
		_pixmap_fill_polygon_cinsert(&pgn, j, y);
	    }
	    j = (i < pgn.n - 1) ? i + 1 : 0;
	    if ((x = (int) pgn.pt[j].y) < y) {
		_pixmap_fill_polygon_cdelete(&pgn, i);
	    } else if (x != y) {
		_pixmap_fill_polygon_cinsert(&pgn, i, y);
	    }
	}
	qsort(pgn.active, pgn.nact, sizeof(pgn.active[0]),
	      _pixmap_fill_polygon_cmpactv);
	for (j = 0; j < pgn.nact; j += 2) {
	    if ((xl = (int) pgn.active[j    ].x) < win.x0) xl = win.x0;
	    if ((xr = (int) pgn.active[j + 1].x) > win.x1) xr = win.x1;
	    for (x = xl; x <= xr; x++)
		pixmap_put_pixel(pixmap, pixel, x, y);
	    pgn.active[j    ].x += pgn.active[j    ].dx;
	    pgn.active[j + 1].x += pgn.active[j + 1].dx;
	}
    }

    free(pgn.active);
    free(ind);

    return;
}

/*----------------------------------------------------------------------*/
static void _pixmap_fill_polygon_cdelete(polygon_t *pgn, int i)
{				/* remove edge i from pgn->active list  */
    int j;

    for (j = 0; j < pgn->nact && pgn->active[j].i != i; j++);

    if (j >= pgn->nact)
	return;

    pgn->nact--;

    memmove(&pgn->active[j], &pgn->active[j + 1],
	    (pgn->nact - j) * sizeof(pgn->active[0]));

    return;
}

/*----------------------------------------------------------------------*/
static void _pixmap_fill_polygon_cinsert(polygon_t *pgn, int i, int y)
{				/* append edge i to end of active list  */
    int j;
    double dx;
    point_t *p, *q;

    j = (i < pgn->n - 1) ? i + 1 : 0;

    if (pgn->pt[i].y < pgn->pt[j].y) {
	p = &pgn->pt[i]; q = &pgn->pt[j];
    } else {
	p = &pgn->pt[j]; q = &pgn->pt[i];
    }

    pgn->active[pgn->nact].dx = dx = (q->x - p->x) / (q->y - p->y);
    pgn->active[pgn->nact].x  = dx * (y - p->y) + p->x;
    pgn->active[pgn->nact].i  = i;
    pgn->nact++;

    return;
}

/*----------------------------------------------------------------------*/
static void _pixmap_fill_polygon_sortidx(polygon_t *pgn, int *index,
					 int first, int last)
{				/* sorting routine for polygon index    */
    int i, j, x, t;

    x = pgn->pt[index[(first + last) / 2]].y;
    i = first; j = last;

    while (1) {
	while (x > pgn->pt[t = index[i]].y) i++;
	while (x < pgn->pt[    index[j]].y) j--;
	if (i >= j) break;
	index[i++] = index[j];
	index[j--] = t;
    }

    if (first < i - 1)
	_pixmap_fill_polygon_sortidx(pgn, index, first, i - 1);

    if (j + 1 < last)
	_pixmap_fill_polygon_sortidx(pgn, index, j + 1, last);

    return;
}

/*----------------------------------------------------------------------*/
static int _pixmap_fill_polygon_cmpactv(const void *p, const void *q)
{				/* comparing routine for qsort          */
    edge_t *u, *v;

    u = (edge_t *) p; v = (edge_t *) q;

    return (u->x < v->x) ? -1 : 1;
}

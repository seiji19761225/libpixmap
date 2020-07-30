/*
 * pixmap_load_pnmfp.c
 * (c)2010-2015 Seiji Nishimura
 * $Id: pixmap_load_pnmfp.c,v 1.1.1.4 2015/12/08 00:00:00 seiji Exp seiji $
 */

#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "pixmap_internal.h"

#ifdef SUPPORT_MULTIBYTE_PNM
#define MAXMV	0xffff
#else
#define MAXMV	0x00ff
#endif

/* PNM image magic numbers */
#define PBM_ASCII	(('P'<<8)|'1')
#define PGM_ASCII	(('P'<<8)|'2')
#define PPM_ASCII	(('P'<<8)|'3')
#define PBM_RAW		(('P'<<8)|'4')
#define PGM_RAW		(('P'<<8)|'5')
#define PPM_RAW		(('P'<<8)|'6')

/* prototype of internal procedures */
static int _pixmap_load_pbma(pixmap_t *, FILE *);
static int _pixmap_load_pgma(pixmap_t *, FILE *);
static int _pixmap_load_ppma(pixmap_t *, FILE *);
static int _pixmap_load_pbmr(pixmap_t *, FILE *);
static int _pixmap_load_pgmr(pixmap_t *, FILE *);
static int _pixmap_load_ppmr(pixmap_t *, FILE *);
static int _pixmap_get_uint (FILE *);
static int _pixmap_get_2b   (FILE *);

/*======================================================================*/
int pixmap_load_pnmfp(pixmap_t *pixmap, FILE *fp)
{				/* load a PNM image and create the pixmap data. */
    int stat;
    int (*pixmap_load_pnm) (pixmap_t *, FILE *);

    assert(pixmap != NULL);
    assert(fp     != NULL);

    switch (_pixmap_get_2b(fp)) {	/* switching with the magic number. */
    case (PBM_ASCII): pixmap_load_pnm = _pixmap_load_pbma; break;
    case (PGM_ASCII): pixmap_load_pnm = _pixmap_load_pgma; break;
    case (PPM_ASCII): pixmap_load_pnm = _pixmap_load_ppma; break;
    case (PBM_RAW  ): pixmap_load_pnm = _pixmap_load_pbmr; break;
    case (PGM_RAW  ): pixmap_load_pnm = _pixmap_load_pgmr; break;
    case (PPM_RAW  ): pixmap_load_pnm = _pixmap_load_ppmr; break;
    default         : return EXIT_FAILURE;
    }

    if ((pixmap->width  = _pixmap_get_uint(fp)) <= 0 ||
	(pixmap->height = _pixmap_get_uint(fp)) <= 0 ||
	feof(fp))
	return EXIT_FAILURE;

    pixmap_create(pixmap, pixmap->width, pixmap->height);

    if ((stat = pixmap_load_pnm(pixmap, fp)) == EXIT_FAILURE)
	pixmap_destroy(pixmap);

    return stat;
}

/*----------------------------------------------------------------------*/
static int _pixmap_load_pbma(pixmap_t *pixmap, FILE *fp)
{					/* load an ASCII-PBM image.     */
    size_t k;
    const size_t wh = (size_t) pixmap->width * pixmap->height;
    const pixel_t black = pixel_set_rgb(0x00, 0x00, 0x00),
		  white = pixel_set_rgb(0xff, 0xff, 0xff);

    for (k = 0; k < wh; k++) {
	int c;
	while (isspace(c = fgetc(fp)) || c == '#')
	    if (c == '#')	/* skip comment line. */
		while ('\n' != (c = fgetc(fp)) &&
		       '\r' !=  c)
		    if (c == EOF)
			return EXIT_FAILURE;
	if (c != '0' &&
	    c != '1')
	    return EXIT_FAILURE;
	pixmap->data[k] = (c == '0') ? white : black;
    }

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
static int _pixmap_load_pgma(pixmap_t *pixmap, FILE *fp)
{				/* load an ASCII-PGM image.             */
    int maxval;
    size_t k;
    const size_t wh = (size_t) pixmap->width * pixmap->height;

    if ((maxval = _pixmap_get_uint(fp)) <= 0 ||
	 maxval > MAXMV)
	return EXIT_FAILURE;

    for (k = 0; k < wh; k++) {
	int c = _pixmap_get_uint(fp);
	if (c < 0 || c > maxval)
	    return EXIT_FAILURE;
	if (maxval != 0xff)
	    c = (int) (255.0 * c / maxval + 0.5);
	pixmap->data[k] = pixel_set_rgb(c, c, c);
    }

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
static int _pixmap_load_ppma(pixmap_t *pixmap, FILE *fp)
{				/* load an ASCII-PPM image.             */
    int maxval;
    size_t k;
    const size_t wh = (size_t) pixmap->width * pixmap->height;

    if ((maxval = _pixmap_get_uint(fp)) <= 0 ||
	 maxval > MAXMV)
	return EXIT_FAILURE;

    for (k = 0; k < wh; k++) {
	int r, g, b;
	if ((r = _pixmap_get_uint(fp)) < 0 || r > maxval ||
	    (g = _pixmap_get_uint(fp)) < 0 || g > maxval ||
	    (b = _pixmap_get_uint(fp)) < 0 || b > maxval)
	    return EXIT_FAILURE;
	if (maxval != 0xff) {
	    r = (int) (255.0 * r / maxval + 0.5);
	    g = (int) (255.0 * g / maxval + 0.5);
	    b = (int) (255.0 * b / maxval + 0.5);
	}
	pixmap->data[k] = pixel_set_rgb(r, g, b);
    }

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
static int _pixmap_load_pbmr(pixmap_t *pixmap, FILE *fp)
{				/* load a raw PBM image.                */
    int i, j;
    size_t k;
    const pixel_t black = pixel_set_rgb(0x00, 0x00, 0x00),
		  white = pixel_set_rgb(0xff, 0xff, 0xff);

    for (k = j = 0; j < pixmap->height; j++)
	for (i = 0; i < pixmap->width ; i++, k++) {
	    int c, s;
	    if ((s = ~i & 0x07) == 7 &&	/* s = 7 - (i % 8) */
		(c = fgetc(fp)) == EOF)
		return EXIT_FAILURE;
	    pixmap->data[k] = (c & (0x01 << s)) ? black : white;
	}

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
static int _pixmap_load_pgmr(pixmap_t *pixmap, FILE *fp)
{				/* load a raw PGM image.                */
    int maxval;
    size_t k;
    int (*get_data) (FILE *);
    const size_t wh = (size_t) pixmap->width * pixmap->height;

    if ((maxval = _pixmap_get_uint(fp)) <= 0 ||
	 maxval > MAXMV)
	return EXIT_FAILURE;

#ifdef SUPPORT_MULTIBYTE_PNM
    get_data = (maxval <= 0xff) ? fgetc : _pixmap_get_2b;
#else
    get_data = fgetc;
#endif

    for (k = 0; k < wh; k++) {
	int c = get_data(fp);
	if (c < 0 || c > maxval)
	    return EXIT_FAILURE;
	if (maxval != 0xff)
	    c = (int) (255.0 * c / maxval + 0.5);
	pixmap->data[k] = pixel_set_rgb(c, c, c);
    }

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
static int _pixmap_load_ppmr(pixmap_t *pixmap, FILE *fp)
{				/* load a raw PPM image.                */
    int maxval;
    size_t k;
    int (*get_data) (FILE *);
    const size_t wh = (size_t) pixmap->width * pixmap->height;

    if ((maxval = _pixmap_get_uint(fp)) <= 0 ||
	 maxval > MAXMV)
	return EXIT_FAILURE;

#ifdef SUPPORT_MULTIBYTE_PNM
    get_data = (maxval <= 0xff) ? fgetc : _pixmap_get_2b;
#else
    get_data = fgetc;
#endif

    for (k = 0; k < wh; k++) {
	int r, g, b;
	if ((r = get_data(fp)) < 0 || r > maxval ||
	    (g = get_data(fp)) < 0 || g > maxval ||
	    (b = get_data(fp)) < 0 || b > maxval)
	    return EXIT_FAILURE;
	if (maxval != 0xff) {
	    r = (int) (255.0 * r / maxval + 0.5);
	    g = (int) (255.0 * g / maxval + 0.5);
	    b = (int) (255.0 * b / maxval + 0.5);
	}
	pixmap->data[k] = pixel_set_rgb(r, g, b);
    }

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
static int _pixmap_get_uint(FILE *fp)
{
    int c, v = 0;

    while (isspace(c = fgetc(fp)) || c == '#')
	if (c == '#')	/* skip comment line. */
	    while ('\n' != (c = fgetc(fp)) &&
		   '\r' !=  c)
		if (c == EOF)
		    return -1;

    if (!isdigit(c))
	return -1;

    do {
	v = 10 * v + c - '0';
    } while (isdigit(c = fgetc(fp)));

    return v;
}

/*----------------------------------------------------------------------*/
static int _pixmap_get_2b(FILE *fp)
{
    int c[2];

    if ((c[0] = fgetc(fp)) == EOF ||
	(c[1] = fgetc(fp)) == EOF)
	return EOF;

    return (c[0] << 8) | c[1];
}

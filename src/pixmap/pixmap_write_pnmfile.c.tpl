/*
 * pixmap_write_pnmfile.c
 * (c)2010-2016 Seiji Nishimura
 * $Id: pixmap_write_pnmfile.c.tpl,v 1.1.1.8 2016/02/16 00:00:00 seiji Exp seiji $
 */

#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pixmap_internal.h"

/* LF is '\n' on UNIX/LINUX. */
#define LF	0x0a

/* visual classes */
#define VC_MONOCHROME	0
#define VC_GRAYSCALE	1
#define VC_TRUECOLOR	2

/* macro functions */
#define SQUARE(x)	((x)*(x))
#ifdef USE_NTSC_LUMIN
#define LUMIN(p)	ROUND(0.299 *pixel_get_r(p)+0.587 *pixel_get_g(p)+0.114 *pixel_get_b(p))
#else
#define LUMIN(p)	ROUND(0.2125*pixel_get_r(p)+0.7154*pixel_get_g(p)+0.0721*pixel_get_b(p))
#endif

/* internal functions */
static int _pixmap_write_pbm          (pixmap_t *, FILE *);
static int _pixmap_write_pgm          (pixmap_t *, FILE *);
static int _pixmap_write_ppm          (pixmap_t *, FILE *);
static int _pixmap_detect_visual_class(pixmap_t *);
static int _pixmap_binary_threshold   (pixmap_t *);

/*======================================================================*/
int pixmap_write_pnmfile(pixmap_t *pixmap, const char *fname)
#ifdef USE_PIPED_GZIP
{				/* write out a PNM image.               */
    FILE *fp;
    int i, m, n,
	istat, pstat;
    char str[256];
    static bool first_call = true;
    const char  *file = "%s",
		*gzip = "__GZIP__ -c9 > %s 2> /dev/null";
    const struct {
	const char *suffix, *format;
	FILE *(*open ) (const char *, const char *);
	int   (*close) (FILE *);
	int   (*write) (pixmap_t *, FILE *);
    } tbl[] = {
	{ ".pbm.Z" , gzip, popen, pclose, _pixmap_write_pbm   },
	{ ".pgm.Z" , gzip, popen, pclose, _pixmap_write_pgm   },
	{ ".ppm.Z" , gzip, popen, pclose, _pixmap_write_ppm   },
	{ ".Z"     , gzip, popen, pclose,  pixmap_write_pnmfp },
	{ ".pbm.gz", gzip, popen, pclose, _pixmap_write_pbm   },
	{ ".pgm.gz", gzip, popen, pclose, _pixmap_write_pgm   },
	{ ".ppm.gz", gzip, popen, pclose, _pixmap_write_ppm   },
	{ ".gz"    , gzip, popen, pclose,  pixmap_write_pnmfp },
	{ ".pbm.z" , gzip, popen, pclose, _pixmap_write_pbm   },
	{ ".pgm.z" , gzip, popen, pclose, _pixmap_write_pgm   },
	{ ".ppm.z" , gzip, popen, pclose, _pixmap_write_ppm   },
	{ ".z"     , gzip, popen, pclose,  pixmap_write_pnmfp },
	{ ".pbm"   , file, fopen, fclose, _pixmap_write_pbm   },
	{ ".pgm"   , file, fopen, fclose, _pixmap_write_pgm   },
	{ ".ppm"   , file, fopen, fclose, _pixmap_write_ppm   },
	{ ""       , file, fopen, fclose,  pixmap_write_pnmfp }	/* sentinel */
    };

    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);
    assert(fname != NULL);

    if (first_call) {
	if (signal(SIGPIPE, (void (*) (int)) abort) == SIG_ERR)
	    return EXIT_FAILURE;
	first_call = false;
    }

    if (strcmp("-", fname) == 0)
	return pixmap_write_pnmfp(pixmap, stdout);

    /* determine PNM file type with the suffix. */
    i = 0; m = strlen(fname);
    while ((n =   m - strlen(tbl[i].suffix)) <= 0 ||
	   strcmp(&fname[n], tbl[i].suffix)  != 0)
	i++;

    assert(i < sizeof(tbl) / sizeof(tbl[0]));

    n = sizeof(str);
    if (snprintf(str, n, tbl[i].format, fname) >= n ||
	(fp = tbl[i].open(str, "w")) == NULL)
	return EXIT_FAILURE;

    istat = tbl[i].write(pixmap, fp);

    if ((pstat = tbl[i].close(fp)) != 0) {	/* critical I/O error */
	if (pstat != EOF)
	    errno = EPIPE;
	return EXIT_FAILURE;
    }

    return istat;
}
#else				/*......................................*/
{				/* write out a PNM image.               */
    FILE *fp;
    int stat, i, m, n;
    const struct {
	const char *suffix;
	int (*function) (pixmap_t *, FILE *);
    } tbl[] = {
	{ ".pbm", _pixmap_write_pbm   },
	{ ".pgm", _pixmap_write_pgm   },
	{ ".ppm", _pixmap_write_ppm   },
	{ ""    ,  pixmap_write_pnmfp }	/* sentinel */
    };

    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);
    assert(fname != NULL);

    if (strcmp("-", fname) == 0)
	return pixmap_write_pnmfp(pixmap, stdout);

    /* determine PNM file type with the suffix. */
    i = 0; m = strlen(fname);
    while ((n =   m - strlen(tbl[i].suffix)) <= 0 ||
	   strcmp(&fname[n], tbl[i].suffix)  != 0)
	i++;

    assert(i < sizeof(tbl) / sizeof(tbl[0]));

    if ((fp = fopen(fname, "wb")) == NULL)
	return EXIT_FAILURE;

    stat = tbl[i].function(pixmap, fp);

    if (fclose(fp) != 0)	/* critical I/O error */
	return EXIT_FAILURE;

    return stat;
}
#endif

/*----------------------------------------------------------------------*/
int pixmap_write_pnmfp(pixmap_t *pixmap, FILE *fp)
{				/* write out a PNM image                */
    int (*_pixmap_write_pnm) (pixmap_t *, FILE *fp);

    assert(pixmap       != NULL);
    assert(pixmap->data != NULL);
    assert(pixmap->width  > 0);
    assert(pixmap->height > 0);
    assert(fp != NULL);

    /* determine PNM file type with the visual class. */
    switch (_pixmap_detect_visual_class(pixmap)) {
    case (VC_MONOCHROME): _pixmap_write_pnm = _pixmap_write_pbm; break;
    case (VC_GRAYSCALE ): _pixmap_write_pnm = _pixmap_write_pgm; break;
    case (VC_TRUECOLOR ): _pixmap_write_pnm = _pixmap_write_ppm; break;
    default             : _pixmap_write_pnm = NULL;
    }

    assert(_pixmap_write_pnm != NULL);

    return _pixmap_write_pnm(pixmap, fp);
}

/*======================================================================*/
/* internal functions                                                   */

/*----------------------------------------------------------------------*/
static int _pixmap_write_pbm(pixmap_t *pixmap, FILE *fp)
{
    int i, j, ii, tlv;
    size_t k;
#ifdef USE_MASK_ARRAY
    const int mask[] = {	/* mask[i] = 0x01 << (7 - i): i=0,1,2,...,7 */
     /* 0x01<<7, 0x01<<6, 0x01<<5, 0x01<<4, 0x01<<3, 0x01<<2, 0x01<<1, 0x01 */
	0x80   , 0x40   , 0x20   , 0x10   , 0x08   , 0x04   , 0x02   , 0x01
    };
#endif

    tlv = _pixmap_binary_threshold(pixmap);

    fprintf(fp, "P4%c%d %d%c", LF, pixmap->width, pixmap->height, LF);

    if (ferror(fp))
	return EXIT_FAILURE;

    for (k = j = 0; j < pixmap->height; j++)
	for (ii = 0; ii < pixmap->width; ii += 8) {
	    int packed_bits = 0x00;
	    for (i = ii; i < MIN(ii + 8, pixmap->width); i++, k++)
		packed_bits |=
#ifdef USE_MASK_ARRAY
		    (LUMIN(pixmap->data[k]) >= tlv) ? 0x00 : mask[i - ii];
#else
		    (LUMIN(pixmap->data[k]) >= tlv) ? 0x00 : (0x01 << (7 - i + ii));
#endif
	    if (fputc(packed_bits, fp) == EOF)
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
static int _pixmap_write_pgm(pixmap_t *pixmap, FILE *fp)
{
    size_t i;
    const size_t wh = (size_t) pixmap->width * pixmap->height;

    fprintf(fp, "P5%c%d %d%c255%c", LF, pixmap->width, pixmap->height, LF, LF);

    if (ferror(fp))
	return EXIT_FAILURE;

    for (i = 0; i < wh; i++)
	if (fputc(LUMIN(pixmap->data[i]), fp) == EOF)
	    return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
static int _pixmap_write_ppm(pixmap_t *pixmap, FILE *fp)
#if SIZEOF_PIXMAP_T == 3
{
    const size_t wh = (size_t) pixmap->width * pixmap->height;

    fprintf(fp, "P6%c%d %d%c255%c", LF, pixmap->width, pixmap->height, LF, LF);

    if (ferror(fp) ||
	fwrite(pixmap->data, sizeof(pixel_t), wh, fp) != wh)
	return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
#else				/* SIZEOF_PIXMAP_T == 4 ................*/
{
    size_t i;
    const size_t wh = (size_t) pixmap->width * pixmap->height;

    fprintf(fp, "P6%c%d %d%c255%c", LF, pixmap->width, pixmap->height, LF, LF);

    if (ferror(fp))
	return EXIT_FAILURE;

    for (i = 0; i < wh; i++)
	if (fputc(pixel_get_r(pixmap->data[i]), fp) == EOF ||
	    fputc(pixel_get_g(pixmap->data[i]), fp) == EOF ||
	    fputc(pixel_get_b(pixmap->data[i]), fp) == EOF)
	    return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
#endif

/*----------------------------------------------------------------------*/
static int _pixmap_detect_visual_class(pixmap_t *pixmap)
{				/* detect visual class of a pixmap.     */
    size_t k;
    const size_t wh = (size_t) pixmap->width * pixmap->height;

    for (k = 0; k < wh; k++)
	if (pixel_get_r(pixmap->data[k]) != pixel_get_g(pixmap->data[k]) ||
	    pixel_get_r(pixmap->data[k]) != pixel_get_b(pixmap->data[k]))
	    return VC_TRUECOLOR;

    for (k = 0; k < wh; k++)
	if (pixel_get_r(pixmap->data[k]) != 0x00 &&
	    pixel_get_r(pixmap->data[k]) != 0xff)
	    return VC_GRAYSCALE;

    return VC_MONOCHROME;
}

/*----------------------------------------------------------------------*/
static int _pixmap_binary_threshold(pixmap_t *pixmap)
{				/* discriminant analysis(Otsu's method) */
    int i, j, k;
    size_t l, histogram[256];
    double avg, max;
    const size_t wh = (size_t) pixmap->width * pixmap->height;

    for (i = 0; i < 256; i++)
	histogram[i] = 0;

    for (l = 0; l < wh; l++)
	histogram[LUMIN(pixmap->data[l])]++;

    avg = 0.0;
    for (i = 0; i < 256; i++)
	avg += histogram[i] * i;
    avg /= wh;

    k   = 0  ;
    max = 0.0;

    for (i = 0; i < 256; i++) {
	size_t count   [2] = { 0  , 0   };
	double class   [2] = { 0.0, 0.0 },
	       average [2] = { 0.0, 0.0 },
	       variance[2] = { 0.0, 0.0 };
	for (j = 0; j < i; j++) {
	    count  [0] += histogram[j];
	    average[0] += histogram[j] * j;
	}
	if (count[0]) {
	    average[0] /= count[0];
	    for (j = 0; j < i; j++)
		variance[0] += SQUARE(average[0] - j) * histogram[j];
	    variance[0] /= count[0];
	}
	for (j = i; j < 256; j++) {
	    count  [1] += histogram[j];
	    average[1] += histogram[j] * j;
	}
	if (count[1]) {
	    average[1] /= count[1];
	    for (j = i; j < 256; j++)
		variance[1] += SQUARE(average[1] - j) * histogram[j];
	    variance[1] /= count[1];
	}
	class[0] = count[0] * variance[0] + count[1] * variance[1];
	class[1] = count[0] * SQUARE(average[0] - avg) +
		   count[1] * SQUARE(average[1] - avg);
	if (class[1] > max * class[0]) {	/* class[1] / class[0] > max */
	    max = class[1] / class[0];
	    k   = i;
	}
    }

    return k;
}

/*
 * pixmap_load_image.c
 * (c)2016 Seiji Nishimura
 * $Id: pixmap_load_image.c,v 1.1.1.3 2016/02/16 00:00:00 seiji Exp seiji $
 */

#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libpixmap/pixmap.h>

/*======================================================================*/
int pixmap_load_image(pixmap_t *pixmap, const char *fname)
{				/* load an image file.                  */
    int i, m, n,
	istat, pstat;
    FILE *fp;
    char str[256];
    static bool first_call = true;
    const char  *file = "%s",
		*gzip = "/usr/bin/zcat -f  %s 2> /dev/null",
#ifdef USE_NETPBM
		*npbm = "/usr/bin/anytopnm %s 2> /dev/null";
#else	/* ImageMagick */
		*imgc = "/usr/bin/convert  %s pnm:- 2> /dev/null";
#endif
    const struct {
	const char *suffix, *format;
	FILE *(*open ) (const char *, const char *);
	int   (*close) (FILE *);
    } tbl[] = {
	{ ".pbm.Z" , gzip, popen, pclose },
	{ ".pgm.Z" , gzip, popen, pclose },
	{ ".ppm.Z" , gzip, popen, pclose },
	{ ".pbm.gz", gzip, popen, pclose },
	{ ".pgm.gz", gzip, popen, pclose },
	{ ".ppm.gz", gzip, popen, pclose },
	{ ".pbm.z" , gzip, popen, pclose },
	{ ".pgm.z" , gzip, popen, pclose },
	{ ".ppm.z" , gzip, popen, pclose },
	{ ".pbm"   , file, fopen, fclose },
	{ ".pgm"   , file, fopen, fclose },
	{ ".ppm"   , file, fopen, fclose },
#ifdef USE_NETPBM
	{ ""       , npbm, popen, pclose }	/* sentinel */
#else	/* ImageMagick */
	{ ""       , imgc, popen, pclose }	/* sentinel */
#endif
    };

    assert(pixmap != NULL);
    assert(fname  != NULL);

    if (first_call) {
	if (signal(SIGPIPE, (void (*) (int)) abort) == SIG_ERR)
	    return EXIT_FAILURE;
	first_call = false;
    }

/*
    if (strcmp("-", fname) == 0)
	return pixmap_load_pnmfp(pixmap, stdin);
 */

    /* determine processing type with the suffix. */
    i = 0; m = strlen(fname);
    while ((n =   m - strlen(tbl[i].suffix)) <= 0 ||
	   strcmp(&fname[n], tbl[i].suffix)  != 0)
	i++;

    assert(i < sizeof(tbl) / sizeof(tbl[0]));

    n = sizeof(str);
    if (snprintf(str, n, tbl[i].format, fname) >= n ||
	(fp = tbl[i].open(str, "r")) == NULL)
	return EXIT_FAILURE;

    istat = pixmap_load_pnmfp(pixmap, fp);

    if ((pstat = tbl[i].close(fp)) != 0) {	/* critical I/O error */
	if (pstat != EOF)
	    errno = EPIPE;
	if (istat == EXIT_SUCCESS)
	    pixmap_destroy(pixmap);
	return EXIT_FAILURE;
    }

    return istat;
}

/*
 * pixmap_load_pnmfile.c
 * (c)2010-2016 Seiji Nishimura
 * $Id: pixmap_load_pnmfile.c.tpl,v 1.1.1.8 2016/02/16 00:00:00 seiji Exp seiji $
 */

#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pixmap_internal.h"

/*======================================================================*/
int pixmap_load_pnmfile(pixmap_t *pixmap, const char *fname)
#ifdef USE_PIPED_GZIP
{				/* load a PNM image.                    */
    int i, m, n,
	istat, pstat;
    FILE *fp;
    char str[256];
    static bool first_call = true;
    const char  *file = "%s",
		*gzip = "__ZCAT__ -f %s 2> /dev/null";
    const struct {
	const char *suffix, *format;
	FILE *(*open ) (const char *, const char *);
	int   (*close) (FILE *);
    } tbl[] = {
	{ ".Z" , gzip, popen, pclose },
	{ ".gz", gzip, popen, pclose },
	{ ".z" , gzip, popen, pclose },
	{ ""   , file, fopen, fclose }	/* sentinel */
    };

    assert(pixmap != NULL);
    assert(fname  != NULL);

    if (first_call) {
	if (signal(SIGPIPE, (void (*) (int)) abort) == SIG_ERR)
	    return EXIT_FAILURE;
	first_call = false;
    }

    if (strcmp("-", fname) == 0)
	return pixmap_load_pnmfp(pixmap, stdin);

    /* determine PNM file type with the suffix. */
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
#else				/*......................................*/
{				/* load a PNM image.                    */
    int stat;
    FILE *fp;

    assert(pixmap != NULL);
    assert(fname  != NULL);

    if (strcmp("-", fname) == 0)
	return pixmap_load_pnmfp(pixmap, stdin);

    if ((fp = fopen(fname, "rb")) == NULL)
	return EXIT_FAILURE;

    stat = pixmap_load_pnmfp(pixmap, fp);

    if (fclose(fp) != 0) {	/* critical I/O error */
	if (stat == EXIT_SUCCESS)
	    pixmap_destroy(pixmap);
	return EXIT_FAILURE;
    }

    return stat;
}
#endif

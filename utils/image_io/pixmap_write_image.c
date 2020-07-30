/*
 * pixmap_write_image.c
 * (c)2016 Seiji Nishimura
 * $Id: pixmap_write_image.c,v 1.1.1.3 2016/02/16 00:00:00 seiji Exp seiji $
 */

#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <libpixmap/pixmap.h>

/*======================================================================*/
int pixmap_write_image(pixmap_t *pixmap, const char *fname)
{				/* write out an image.                  */
    FILE *fp;
    int i, m, n,
	istat, pstat;
    char str[256];
    static bool first_call = true;
    const char  *file = "%s",
		*gzip = "/usr/bin/gzip -c9 > %s 2> /dev/null",
		*imgc = "/usr/bin/convert  - %s 2> /dev/null";
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
	{ ""       , imgc, popen, pclose }	/* sentinel */
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

/*
    if (strcmp("-", fname) == 0)
	return pixmap_write_pnmfp(pixmap, stdout);
 */

    /* determine processing type with the suffix. */
    i = 0; m = strlen(fname);
    while ((n =   m - strlen(tbl[i].suffix)) <= 0 ||
	   strcmp(&fname[n], tbl[i].suffix)  != 0)
	i++;

    assert(i < sizeof(tbl) / sizeof(tbl[0]));

    n = sizeof(str);
    if (snprintf(str, n, tbl[i].format, fname) >= n ||
	(fp = tbl[i].open(str, "w")) == NULL)
	return EXIT_FAILURE;

    istat = pixmap_write_pnmfp(pixmap, fp);

    if ((pstat = tbl[i].close(fp)) != 0) {	/* critical I/O error */
	if (pstat != EOF)
	    errno = EPIPE;
	return EXIT_FAILURE;
    }

    return istat;
}

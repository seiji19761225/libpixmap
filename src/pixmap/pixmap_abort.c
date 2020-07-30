/*
 * pixmap_abort.c
 * (c)2012-2015 Seiji Nishimura
 * $Id: pixmap_abort.c,v 1.1.1.3 2016/01/15 00:00:00 seiji Exp seiji $
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pixmap_internal.h"

/*======================================================================*/
void _pixmap_abort(const char *msg, const char *file, const int line)
#ifdef NDEBUG
{				/* error handler (for production build) */
    if (errno == 0) {
	fprintf(stderr, "%s: unknown error\n", msg);
    } else {			/* system error */
	perror(msg);
    }

    exit(EXIT_FAILURE);

    return;
}
#else				/*......................................*/
{				/* error handler                        */
    char *description = "unknown error (or wrong usage)";

    if (errno != 0)		/* system error */
	description = strerror(errno);

    fprintf(stderr, "%s: %s @line#%d in %s\n", msg, description, line, file);

#ifdef DEBUG
    abort();
#else
    exit(EXIT_FAILURE);
#endif

    return;
}
#endif

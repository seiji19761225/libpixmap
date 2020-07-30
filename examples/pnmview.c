/*
 * pnmview.c: PNM image viewer
 * (c)2012-2016 Seiji Nishimura
 * $Id: pnmview.c,v 1.1.1.4 2016/01/20 00:00:00 seiji Exp seiji $
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <libpixmap/window.h>

#if 0
#define STDIN	"-"
#else
#define STDIN	"/dev/stdin"
#endif

/* function prototypes */
int  display_image(const char *);
void event_loop   (window_t   *);

/*======================================================================*/
int main(int argc, char **argv)
{
    if (argc == 1) {
	if (display_image(STDIN) == EXIT_FAILURE)
	    return EXIT_FAILURE;
    } else {
	int i;
	for (i = 1; i < argc; i++)
	    if (display_image(argv[i]) == EXIT_FAILURE)
		return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
int display_image(const char *fname)
{				/* display a PNM image                  */
    window_t  w;
    window_t *window = &w;

    errno = 0;		/* to reset error    */

    if (window_load_pnmfile(window, fname) == EXIT_FAILURE) {
	if (errno)	/* system error      */
	    perror(fname);
	else		/* file format error */
	    fprintf(stderr, "%s: Not a ppm, pgm, or pbm file\n", fname);
	return EXIT_FAILURE;
    }

    event_loop  (window);
    window_close(window);

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
void event_loop(window_t *window)
{				/* window event loop                    */
    int device, code, x, y;

    do {
	window_get_input(window, true, &device, &code, &x, &y);
    } while (device != WD_KeyBoard);

    return;
}

/*
 * star.c: rolling star (alpha blending demo)
 * (c)2010-2016 Seiji Nishimura
 * $Id: star.c,v 1.1.1.5 2016/01/20 00:00:00 seiji Exp seiji $
 */

#include <math.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libpixmap/window.h>
#include <libpixmap/palette.h>

#define SIZE	(0x01<<8)
#define FREQ	(0x01<<10)
#define RADIUS	(SIZE/2)
#define CTYPE	IDL2_BLUE_RED

#define DEFAULT_TILE	".texture/tux.ppm"

/* position of the star */
#define STAR_X	(SIZE/2)
#define STAR_Y	(SIZE/2)

#define ROUND(x)	((int) round(x))

/* prototype */
bool esc_is_pushed(window_t *);

/*======================================================================*/
int main(int argc, char *argv[])
{
    char *fname = DEFAULT_TILE;
    int i, j, t = 0;
    window_t  w;
    window_t *window = &w;
    pixmap_t  b, s;
    pixmap_t *base   = &b,
	     *star   = &s;
    pixel_t   pixel;

    if (argc > 1)	/* file name is given. */
	fname = argv[argc - 1];

    if (pixmap_load_pnmfile(base, fname) == EXIT_FAILURE) {
	if (errno) {	/* system error        */
	    perror(fname);
	} else {	/* wrong file format   */
	    fprintf(stderr, "%s: Not a ppm, pgm, or pbm file\n", fname);
	}
	exit(EXIT_FAILURE);
    }

    window_open(window, SIZE, SIZE, "star");

    for (j = 0; j < SIZE; j++)	/* generate tiled image. */
	for (i = 0; i < SIZE; i++) {
	    pixmap_get_pixel(base  , &pixel,
				i % base->width, j % base->height);
	    window_put_pixel(window,  pixel, i, j);
	}

    pixmap_destroy(base);

    window_update_image(window);
    window_get_subimage(window, STAR_X - RADIUS, STAR_Y - RADIUS,
			base  , SIZE, SIZE);
    pixmap_create      (star  , SIZE, SIZE);

    do {
	int x[5], y[5];
	double phi   = 2.0 * M_PI * (t = (t + 1) % FREQ) / FREQ,
	       alpha = 1.0 - sin(0.5 * phi);
	for (i = 0; i < 5; i++) {	/* star */
	    double r     = 0.5 * (1.0 - cos(2.0 * phi)),
		   theta = M_PI * (0.8 * i + 2.0 * cos(phi));
	    x[i] = ROUND(RADIUS * (1.0 + r * cos(theta)));
	    y[i] = ROUND(RADIUS * (1.0 - r * sin(theta)));
	}
	pixel = palette(CTYPE, -1.0, 1.0, sin(phi));
/*	pixmap_copy_image     (base  , star); */
	pixmap_fill_polygon   (star  , pixel, 5, x, y);
	pixmap_blend_image    (alpha , base , star);
	window_put_subimage   (window, STAR_X - RADIUS, STAR_Y - RADIUS,
			       star  , 0, 0, SIZE, SIZE);
	window_update_subimage(window, STAR_X - RADIUS, STAR_Y - RADIUS,
					      SIZE, SIZE);
	usleep(5E4);	/* sleep 0.05sec.       */
    } while (!esc_is_pushed(window));

    pixmap_destroy(star  );
    pixmap_destroy(base  );
    window_close  (window);

    return 0;
}

/*----------------------------------------------------------------------*/
bool esc_is_pushed(window_t *window)
{				/* detect ESC key input.                */
    int device, code, x, y;

    do {
	window_get_input(window, false, &device, &code, &x, &y);
    } while (device != WD_Null &&
	    (device != WD_KeyBoard || code != WK_ESC));

    return   device == WD_KeyBoard && code == WK_ESC;
}

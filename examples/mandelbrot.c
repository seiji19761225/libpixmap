/*
 * mandelbrot.c: Mandelbrot set
 * (c)2012-2015 Seiji Nishimura
 * The original code was written by Chisato Yamauchi.
 * $Id: mandelbrot.c,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <math.h>
#include <stdio.h>
#include <libpixmap/pixmap.h>
#include <libpixmap/palette.h>

/* window size */
#define WIDTH		400
#define HEIGHT		400

/* color mode */
#define MY_COLOR	DS9_B

/* parameter set for Mandelbrot set */
#define REAL_BEGIN	0.075
#define REAL_END	0.175
#define IMAG_BEGIN	0.59
#define IMAG_END	0.69
#define LIMIT		(0x01<<10)
#define BAILOUT		4.0

/* prototypes */
int  mandelbrot   (double, double);
void draw_colorbar(pixmap_t *, int, int, int, int);

/*======================================================================*/
int main(int argc, char **argv)
{
    int  x, y, iter;
    pixel_t   pixel;
    pixmap_t pixmap;
    const double  r_step = (REAL_END - REAL_BEGIN) / WIDTH,
		  i_step = (IMAG_END - IMAG_BEGIN) / HEIGHT;

    pixmap_create(&pixmap, WIDTH, HEIGHT);

    /* draw the Mandelbrot set image. */
#pragma omp parallel for private(x,y,iter,pixel)
    for (y = 0; y < HEIGHT; y++) {
	double p_i = IMAG_END - y * i_step;
	for (x = 0; x < WIDTH; x++) {
	    double p_r = REAL_BEGIN + x * r_step;
	    if ((iter = mandelbrot(p_r, p_i)) != 0) {
		pixel = palette(MY_COLOR, 0.0, log(LIMIT), log(iter));
		pixmap_put_pixel(&pixmap, pixel, x, y);
	    }
	}
    }

    draw_colorbar(&pixmap, 16, 8, 128, 16);

    pixmap_write_pnmfile(&pixmap, "mandelbrot.ppm");

    pixmap_destroy(&pixmap);

    return 0;
}

/*----------------------------------------------------------------------*/
int mandelbrot(double p_r, double p_i)
{				/* Mandelbrot function: Z=Z^2+P         */
    int i;
    double tmp, zr2, zi2, z_r = 0.0, z_i = 0.0;

    for (i = 0; i < LIMIT; i++) {
	if ((zr2 = z_r * z_r) +
	    (zi2 = z_i * z_i) >= BAILOUT)
	    break;
	tmp = p_r + zr2 - zi2;
	z_i = p_i + 2.0 * z_r * z_i;
	z_r = tmp;
    }

    return (i == LIMIT) ? 0 : i;
}

/*----------------------------------------------------------------------*/
void draw_colorbar(pixmap_t *pixmap, int x, int y, int width, int height)
{				/* draw colorbar image at (x, y).       */
    int i;
    char  buf[16];
    pixel_t pixel;
    const pixel_t white  = pixel_set_rgb(0xff, 0xff, 0xff);

    for (i = 0; i < width; i++) {
	pixel = palette(MY_COLOR, 0.0, width, i);
	pixmap_draw_line(pixmap, pixel, i + x, y,
					i + x, y + height - 1);
    }

    sprintf(buf, "%.1f", log(1.0  ));
    pixmap_draw_string(pixmap, white, x         - FONT_WIDTH, y + height + 4, buf);
    sprintf(buf, "%.1f", log(LIMIT));
    pixmap_draw_string(pixmap, white, x + width - FONT_WIDTH, y + height + 4, buf);

    return;
}

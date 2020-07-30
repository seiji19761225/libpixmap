/*
 * cplot.c: plot a complex function
 * (c)2012-2015 Seiji Nishimura, based on Wikipedia's sample code
 * The original code is written by Claudio Rocchini.
 * $Id: cplot.c,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <math.h>
#include <complex.h>
#include <libpixmap/pixmap.h>

#define WIDTH	 	400
#define HEIGHT	 	400

#define CENTER_R	0.0
#define CENTER_I	0.0
#define RADIUS		3.0

#define D		(2.0*RADIUS/MIN(WIDTH,HEIGHT))
#define R_MIN	 	(CENTER_R-0.5*D*WIDTH)
#define I_MAX	 	(CENTER_I+0.5*D*HEIGHT)
#define FLOOR(x)	((int) floor(x))
#define MIN(x,y)	(((x)<(y))?(x):(y))

// prototypes
double complex func     (double complex);
void           cmplx2hsv(double complex, double *, double *, double *);
pixel_t        hsv2rgb  (double, double, double);

/*======================================================================*/
int main(int argc, char **argv)
{
    int i, j;
    pixmap_t pixmap;

    pixmap_create(&pixmap, WIDTH, HEIGHT);

#pragma omp parallel for private(i,j)
    for (j = 0; j < HEIGHT; j++)
	for (i = 0; i < WIDTH; i++) {
	    double hue, sat, val;
	    pixel_t pixel;
	    cmplx2hsv(func((R_MIN + D * i) + (I_MAX - D * j) * I),
		      &hue, &sat, &val);
	    pixel = hsv2rgb(hue, sat, val);
	    pixmap_put_pixel(&pixmap, pixel, i, j);
	}

    pixmap_write_pnmfile(&pixmap, "cplot.ppm");

    pixmap_destroy(&pixmap);

    return 0;
}

/*----------------------------------------------------------------------*/
double complex func(double complex c)
{				/* complex function to visualize        */
    return (c * c - 1.0) * (c - 2.0 - I) * (c - 2.0 - I) /
	   (c * c + 2.0 + 2.0 * I);
}

/*----------------------------------------------------------------------*/
void cmplx2hsv(double complex z, double *hue, double *sat, double *val)
{		/* convert a complex number to the (H,S,V) color.       */
    double m;

    if ((m = cabs(z)) >= 1.0)
	m = fmod(log(m), 1.0);

    *sat = 1.0 - (*val = (m < 0.5) ? 2.0 * m : 1.0 - (m - 0.5) * 2.0);

    if ((*hue = carg(z) / (2.0 * M_PI)) < 0.0)
	*hue += 1.0;

    *sat = 1.0 - 0.6 * *sat * *sat * *sat;
    *val = 1.0 - 0.4 * *val * *val * *val;

    return;
}

/*----------------------------------------------------------------------*/
pixel_t hsv2rgb(double h, double s, double v)
{		/* convert a (H,S,V) color to the (R,G,B) color.        */
    double r, g, b;

    if (s == 0.0) {
	r = g = b = v;
    } else {
	double  z, f, p, q, t;
	if (h == 1.0) h = 0.0;
	z = floor(6.0 * h); f = 6.0 * h  - z;
	p =  v * (1.0 - s); q = v * (1.0 - s * f);
	t =  v * (1.0 - s * (1.0 - f));
	switch ((int) z) {
	case (0): r = v; g = t; b = p; break;
	case (1): r = q; g = v; b = p; break;
	case (2): r = p; g = v; b = t; break;
	case (3): r = p; g = q; b = v; break;
	case (4): r = t; g = p; b = v; break;
	default : r = v; g = p; b = q; break;
	}
    }

    return pixel_set_rgb(FLOOR(255 * r), FLOOR(255 * g), FLOOR(255 * b));
}

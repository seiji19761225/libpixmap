/* 
 * roche.c: Roche Potential World
 * (c)2012-2016 Seiji Nishimura
 * The original code is written by Chisato Yamauchi.
 * $Id: roche.c,v 1.1.1.5 2016/01/20 00:00:00 seiji Exp seiji $
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <libpixmap/window.h>
#include <libpixmap/palette.h>

#define DELTA		1.E-3

/* Mass Ratio   */
#define MRATIO_F	0.23

/* Field        */
#define XMIN		-1.5
#define XMAX		+1.5
#define YMIN		-1.5
#define YMAX		+1.5
#define ZMIN		-3.5
#define ZMAX		-1.4

#define XCNST		((XMAX-XMIN)/(WIDTH -1.0))
#define YCNST		((YMAX-YMIN)/(HEIGHT-1.0))

/* window size  */
#define WIDTH		400
#define HEIGHT		400

/* mesh size    */
#define DI		16
#define DJ		16

#define VXSCALE		16.0
#define VYSCALE		16.0
#define VCARMAX		32.0

#define ARROW_HEAD	AH_TYPE5

/* event action */
#define EXIT		0
#define RECALC		1
#define REDRAW		2

#define MIN(x,y)	(((x)<(y))?(x):(y))

#define alloc_2d_array(n,m,t)	((t **) allocate_2d_array(n,m,sizeof(t)))
#define free_2d_array(p)	deallocate_2d_array((char *)(p))

typedef struct {
    bool   mosaic;
    int    ctype ;
    double f, zcen, zran;
} prms_t;

/* global variables */
static double **fx = NULL, **fy = NULL, **phi = NULL;

/* prototypes       */
void   mosaic_view        (window_t *, prms_t *);
void   simple_view        (window_t *, prms_t *);
void   vector_field       (window_t *);
int    event_action       (window_t *, prms_t *);
double get_fx             (double, double, double);
double get_fy             (double, double, double);
double get_phi            (double, double, double);
void  *allocate_2d_array  (size_t, size_t, size_t);
void   deallocate_2d_array(void *);

/*======================================================================*/
int main(int argc, char **argv)
{
    int i, j, action = RECALC;
    prms_t    p;
    prms_t   *prms   = &p;
    window_t  w;
    window_t *window = &w;

    /* default parameters */
    prms->mosaic = true;
    prms->ctype  = IDL2_BLUE_RED;
    prms->f      = MRATIO_F;
    prms->zcen   = (ZMAX + ZMIN) / 2.0;
    prms->zran   =  ZMAX - ZMIN;

    if ((fx  = alloc_2d_array(HEIGHT, WIDTH, double)) == NULL ||
	(fy  = alloc_2d_array(HEIGHT, WIDTH, double)) == NULL ||
	(phi = alloc_2d_array(HEIGHT, WIDTH, double)) == NULL) {
	perror(argv[0]);
	return EXIT_FAILURE;
    }

    window_open(window,  WIDTH, HEIGHT, "Roche Potential World");

    do {
	switch (action) {
	case (RECALC):
#pragma omp parallel for private(i,j)
	    for (j = 0; j < HEIGHT; j++) {
		double y = YMIN + j * YCNST;
		for (i = 0; i < WIDTH; i++) {
		    double x = XMIN + i * XCNST;
		    phi[j][i] = get_phi(x, y, prms->f);
		    fx [j][i] = get_fx (x, y, prms->f) * VXSCALE;
		    fy [j][i] = get_fy (x, y, prms->f) * VYSCALE;
		}
	    }
	case (REDRAW):
#pragma omp parallel
	    (prms->mosaic ? mosaic_view : simple_view) (window, prms);
	    window_update_image(window);
	default:
	    break;
	}
    } while ((action = event_action(window, prms)) != EXIT);

    window_close(window);

    free_2d_array(phi);
    free_2d_array(fy );
    free_2d_array(fx );

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
void mosaic_view(window_t *window, prms_t *prms)
{
    int i, j, k, ii, jj, sum_r, sum_g, sum_b;
    pixel_t pixel;

#pragma omp for
    for (jj = 0; jj < HEIGHT; jj += DJ)
	for (ii = 0; ii < WIDTH; ii += DI) {
	    sum_r = sum_g = sum_b = 0;
	    for (k = 0, j = jj; j < MIN(HEIGHT, jj + DJ); j++)
		for (   i = ii; i < MIN(WIDTH , ii + DI); i++, k++) {
		    pixel = palette(prms->ctype,
				     prms->zcen - prms->zran / 2.0,
				     prms->zcen + prms->zran / 2.0, phi[j][i]);
		    sum_r += pixel_get_r(pixel);
		    sum_g += pixel_get_g(pixel);
		    sum_b += pixel_get_b(pixel);
		}
	    pixel = pixel_set_rgb(sum_r / k, sum_g / k, sum_b / k);
	    window_clear_subimage(window, pixel, ii, jj, DI, DJ);
	}

#pragma omp single
    vector_field(window);

    return;
}

/*----------------------------------------------------------------------*/
void simple_view(window_t *window, prms_t *prms)
{
    int i, j;
    pixel_t pixel;

#pragma omp for
    for (j = 0; j < HEIGHT; j++)
	for (i = 0; i < WIDTH; i++) {
	    pixel = palette(prms->ctype,
			     prms->zcen - prms->zran / 2.0,
			     prms->zcen + prms->zran / 2.0, phi[j][i]);
	    window_put_pixel(window, pixel, i, j);
	}

#pragma omp single
    vector_field(window);

    return;
}

/*----------------------------------------------------------------------*/
void vector_field(window_t *window)
{
    int i, j;
    double z, zx, zy;
    const pixel_t white = pixel_set_rgb(0xff, 0xff, 0xff);

    for (j = DJ / 2; j < HEIGHT; j += DJ)
	for (i = DI / 2; i < WIDTH; i += DI)
	    if ((z = hypot(zx = fx[j][i],
			   zy = fy[j][i])) <= VCARMAX)
		window_draw_arrow(window, white, false, true, ARROW_HEAD,
					0.25 * z, 0.5 * z, i, j, i + zx, j + zy);

    return;
}

/*----------------------------------------------------------------------*/
int event_action(window_t *window, prms_t *prms)
{
    int i, j, device, code,
	action = REDRAW;

    window_get_input(window, true, &device, &code, &i, &j);

    do {
	if (device == WD_KeyBoard) {
	    switch (code) {
	    case (WK_ESC):                             action = EXIT;   break;
	    case (WK_PageUp):   prms->f      += DELTA; action = RECALC; break;
	    case (WK_PageDown): prms->f      -= DELTA; action = RECALC; break;
	    case (WK_Up):       prms->zcen   += DELTA;                  break;
	    case (WK_Down):     prms->zcen   -= DELTA;                  break;
	    case (WK_Right):    prms->zran   += DELTA;                  break;
	    case (WK_Left):     prms->zran   -= DELTA;                  break;
	    case (' '):         prms->mosaic ^= true;                   break;
	    case ('C'):         prms->ctype++;                          break;
	    case ('c'):         prms->ctype--;                          break;
/*	    default:                                                    break; */
	    }
	    if (prms->ctype >= PALETTE_NTYPES) prms->ctype = 0;
	    if (prms->ctype <  0             ) prms->ctype = PALETTE_NTYPES - 1;
	    if (prms->f     <  0.0           ) prms->f     = 0.0;
	    if (prms->zran  <  DELTA         ) prms->zran  = DELTA;
	}
	window_get_input(window, false, &device, &code, &i, &j);
    } while (action != EXIT && device != WD_Null);

    return action;
}

/*----------------------------------------------------------------------*/
double get_fx(double x, double y, double f)
{
    double fx0, fx1;

    fx0 = -(x + f   / (1.0 + f))     /
	pow(pow(x + f   / (1.0 + f), 2.0) + y * y, 3.0 / 2.0);
    fx1 = -(x - 1.0 / (1.0 + f)) * f /
	pow(pow(x - 1.0 / (1.0 + f), 2.0) + y * y, 3.0 / 2.0);

    return fx0 + fx1 + (1.0 + f) * x;
}

/*----------------------------------------------------------------------*/
double get_fy(double x, double y, double f)
{
    double fy0, fy1;

    fy0 = -y /     pow(pow(x + f   / (1.0 + f), 2.0) + y * y, 3.0 / 2.0);
    fy1 = -y * f / pow(pow(x - 1.0 / (1.0 + f), 2.0) + y * y, 3.0 / 2.0);

    return fy0 + fy1 + (1.0 + f) * y;
}

/*----------------------------------------------------------------------*/
double get_phi(double x, double y, double f)
{
    return -1.0 / sqrt(pow(x + f   / (1.0 + f), 2.0) + y * y)
	   -f   / sqrt(pow(x - 1.0 / (1.0 + f), 2.0) + y * y)
	   - (1.0 + f) * (x * x + y * y) / 2.0;
}

/*----------------------------------------------------------------------*/
void *allocate_2d_array(size_t nrow, size_t ncol, size_t size)
{				/* allocate a 2D array.                 */
    size_t i;
    char **p;

    if ((p    = (char **) malloc(nrow * sizeof(char *))) == NULL ||
	(p[0] = (char  *) malloc(nrow * ncol * size))    == NULL) {
	free(p); return NULL;
    }

    for (i = 1; i < nrow; i++)	/* setting up pointers */
	p[i] = &p[0][i * ncol * size];

    return (void *) p;
}

/*----------------------------------------------------------------------*/
void deallocate_2d_array(void *p)
{				/* deallocate a 2D array.               */
    char **q;

    if ((q = (char **) p) != NULL) {
	free(q[0]); free(q);
    }

    return;
}

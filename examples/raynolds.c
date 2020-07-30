/*
 * raynolds.c: SIGGRAPH1987 Craig Raynolds
 *             "Flocks, Herds, and Schools: A Distributed Behavioral Model"
 * (c)2012-2016 Seiji Nishimura
 * The original code is written by Chisato Yamauchi.
 * $Id: raynolds.c,v 1.1.1.4 2016/01/20 00:00:00 seiji Exp seiji $
 */

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libpixmap/window.h>

#define WW	600		/* width                        */
#define HH	600		/* height                       */
#define TH	20		/* wall position                */
#define RR	9		/* radius of a circle           */
#define SS	8.0		/* standard speed               */
#define DD	30.0		/* radius of schools            */
#define MM	300		/* maxmum number of individuals */

/* frame */
#define TOP	(TH)
#define LEFT	(TH)
#define RIGHT	(WW-TH)
#define BOTTOM	(HH-TH)

#define MALLOC(n,t)	((t *) malloc((n)*sizeof(t)))

static int mm       = 0,	/* number of individuals */
	   interval = 0;	/* clock interval        */
static double *xx = NULL, *yy = NULL,	/* coordinates   */
	      *xv = NULL, *yv = NULL,	/* velocities    */
	      *xw = NULL, *yw = NULL;	/* work arrays   */

/* prototypes */
double  drand        (double);
void    drawit       (window_t *, int);
void    moveit       (int);
pixel_t newhsvcolor  (int, int, int);
bool    esc_is_pushed(window_t *);

/*=====================================================================*/
int main(int argc, char **argv)
{
    int i, j, frame_x[4], frame_y[4];
    window_t  w;
    window_t *window = &w;
    const pixel_t black = pixel_set_rgb(0x00, 0x00, 0x00),
		  white = pixel_set_rgb(0xff, 0xff, 0xff);

    srand((int) time(NULL));

    switch (argc) {
    case (1): mm = MM;            interval = 40;            break;
    case (2): mm = atoi(argv[1]); interval = 40;            break;
    case (3): mm = atoi(argv[1]); interval = atoi(argv[2]); break;
    default:
	fprintf(stderr, "usage: %s [num [msec]]\n", argv[0]);
	return EXIT_FAILURE;
    }

    if (mm       < 1 || mm       > MM  ) {
	fprintf(stderr, "usage: %s [num [msec]]\n"
			"     : given num (%s) is not from 1 to %d\n",
		argv[0], argv[1], MM);
	return EXIT_FAILURE;
    }

    if (interval < 1 || interval > 1000) {
	fprintf(stderr, "usage: %s [num [msec]]\n"
			"     : given msec (%s) is not from 1 to 1000\n",
		argv[0], argv[2]);
	return EXIT_FAILURE;
    }

    /* frame */
    frame_x[0] =  LEFT; frame_y[0] =    TOP;
    frame_x[1] = RIGHT; frame_y[1] =    TOP;
    frame_x[2] = RIGHT; frame_y[2] = BOTTOM;
    frame_x[3] =  LEFT; frame_y[3] = BOTTOM;

    if ((xx = MALLOC(mm, double)) == NULL || (yy = MALLOC(mm, double)) == NULL ||
	(xv = MALLOC(mm, double)) == NULL || (yv = MALLOC(mm, double)) == NULL ||
	(xw = MALLOC(mm, double)) == NULL || (yw = MALLOC(mm, double)) == NULL) {
	perror(argv[0]);
	return EXIT_FAILURE;
    }

#pragma omp parallel for
    for (i = 0; i < mm; i++) {	/* set up the initial status. */
	double r, t;
	xx[i] = WW / 6.0 * (3.0 + (r = drand(1.0)) * cos(t = drand(2.0 * M_PI)));
	yy[i] = HH / 6.0 * (3.0 +  r               * sin(t));
	xv[i] = SS * cos(t = drand(2.0 * M_PI));
	yv[i] = SS * sin(t);
    }

    window_open(window, WW, HH, "Raynolds");

    do {	/* time steps */
	window_clear_image(window, black);
	for (j = 3, i = 0; i < 4; j = i++)	/* frame */
	    window_draw_line(window, white, frame_x[i], frame_y[i],
					    frame_x[j], frame_y[j]);
	for (i = 0; i < mm; i++)
	    drawit(window, i);
	window_update_image(window);
#pragma omp parallel for
	for (i = 0; i < mm; i++)
	    moveit(i);
#pragma omp parallel for
	for (i = 0; i < mm; i++) {
	    xx[i] += (xv[i] = xw[i]);
	    yy[i] += (yv[i] = yw[i]);
	    if (xx[i] < LEFT  ) xv[i] =  fabs(xv[i]);
	    if (xx[i] > RIGHT ) xv[i] = -fabs(xv[i]);
	    if (yy[i] < TOP   ) yv[i] =  fabs(yv[i]);
	    if (yy[i] > BOTTOM) yv[i] = -fabs(yv[i]);
	}
	usleep(1E3 * interval);
    } while (!esc_is_pushed(window));

    window_close(window);

    free(yw); free(xw);
    free(yv); free(xv);
    free(yy); free(xx);

    return EXIT_SUCCESS;
}

/*---------------------------------------------------------------------*/
double drand(double ratio)
{				/* random number generator             */
    int rnd;

#pragma omp critical
    rnd = rand();

    return ratio * rnd / (RAND_MAX + 1.0);
}

/*---------------------------------------------------------------------*/
void drawit(window_t *window, int i)
{				/* draw #i-th individual.              */
    int x, y;
    double  ratio;
    pixel_t pixel;

    x = xx[i]; y = yy[i];

    ratio = 3.0 * RR / hypot(xv[i], yv[i]);
    pixel = newhsvcolor(0, 0, 200);
    window_draw_line(window, pixel, x, y,
		     x - xv[i] * ratio, y - yv[i] * ratio);

    pixel = newhsvcolor(360 * i / mm, 255, 255);
    window_fill_ellipse(window, pixel, x, y, RR, RR);

    pixel = newhsvcolor(0, 0, 128);
    window_draw_ellipse(window, pixel, x, y, RR, RR);

    return;
}

/*---------------------------------------------------------------------*/
void moveit(int i)
{				/* move #i-th individual.              */
    int j, num;
    double x, y, dtmp, ratio, limit, dist[MM];

    xw[i] = xv[i]; yw[i] = yv[i];

    /* alignment ......................................................*/
    limit = DD;
    ratio = 0.6 + drand(0.6);
    num   = 0; x = y = 0.0;
    for (j = 0; j < mm; j++) {	/* interaction with other individuals  */
	if (i == j) continue;
	if ((dist[j] = hypot(xx[i] - xx[j], yy[i] - yy[j])) < limit) {
	    x += xv[j];
	    y += yv[j];
	    num++;
	}
    }

    if (num) {
	x /= num;
	y /= num;
	x *= (dtmp = ratio * SS / hypot(x, y));
	y *=  dtmp;
	xw[i] = 0.7 * xv[i] + 0.3 * x;
	yw[i] = 0.7 * yv[i] + 0.3 * y;
    }

    /* separation .....................................................*/
    limit = 0.6 * DD;
    ratio = 0.6 + drand(1.4);
    num   = 0; x = y = 0.0;
    for (j = 0; j < mm; j++) {	/* interaction with other individuals  */
	if (i == j) continue;
	if (dist[j] < limit) {
	    x += (xx[i] - xx[j]) * (dtmp = 1.0 - dist[j] / limit);
	    y += (yy[i] - yy[j]) *  dtmp;
	    num++;
	}
    }

    if (num) {
	xw[i] = x * ratio / num;
	yw[i] = y * ratio / num;
    }

    /* cohesion .......................................................*/
    limit = DD;
    ratio = 0.01 + drand(0.05);
    num   = 0; x = y = 0.0;
    for (j = 0; j < mm; j++) {	/* interaction with other individuals  */
	if (i == j) continue;
	if (dist[j] < limit) {
	    x += xx[j];
	    y += yy[j];
	    num++;
	}
    }

    if (num) {
	x = x / num - xx[i];
	y = y / num - yy[i];
	if (SS < (dtmp = hypot(x, y))) {
	    x *= (dtmp = SS / dtmp);
	    y *=  dtmp;
	}
	xw[i] += x * ratio;
	yw[i] += y * ratio;
    }

    /* fluctuation ....................................................*/
    xw[i] += SS * (drand(0.4) - 0.2);
    yw[i] += SS * (drand(0.4) - 0.2);

    return;
}

/*---------------------------------------------------------------------*/
pixel_t newhsvcolor(int h, int s, int v)
{				/* HSV color                           */
    pixel_t pixel;

    if (s == 0) {
	pixel = pixel_set_rgb(v, v, v);
    } else {
	int c1, c2, c3, t;
	t  = (h * 6) % 360;
	c1 = (v * (255 - s)) / 255;
	c2 = (v * (255 - (s * t) / 360)) / 255;
	c3 = (v * (255 - (s * (360 - t)) / 360)) / 255;
	switch (h / 60) {
	case 0 : pixel = pixel_set_rgb(v , c3, c1); break;
	case 1 : pixel = pixel_set_rgb(c2, v , c1); break;
	case 2 : pixel = pixel_set_rgb(c1, v , c3); break;
	case 3 : pixel = pixel_set_rgb(c1, c2, v ); break;
	case 4 : pixel = pixel_set_rgb(c3, c1, v ); break;
	default: pixel = pixel_set_rgb(v , c1, c2); break;
	}
    }

    return pixel;
}

/*---------------------------------------------------------------------*/
bool esc_is_pushed(window_t *window)
{				/* detect ESC key input.               */
    int device, code, x, y;

    do {
	window_get_input(window, false, &device, &code, &x, &y);
    } while (device != WD_Null &&
	    (device != WD_KeyBoard || code != WK_ESC));

    return   device == WD_KeyBoard && code == WK_ESC;
}

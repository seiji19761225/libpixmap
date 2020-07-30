/*
 * gray-scott.c: Gray-Scott Model Reaction Diffusion System (GS-RDS)
 * (c)2012-2016 Seiji Nishimura
 * $Id: gray-scott.c,v 1.1.1.4 2016/01/20 00:00:00 seiji Exp seiji $
 */

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libpixmap/window.h>

#define WIDTH	400
#define HEIGHT	400

/* simulation parameters */
#define TI	(0x01<<2)	/* display graphics on window every TI steps */
#define DT	1.0		/* single time step period */
#define DU	0.05
#define DV	0.0235
#define F	0.03
#define K	0.0535

/* initial state */
#define P	200
#define R	5
/* stable state (Us, Vs) */
#define US	1.0
#define VS	0.0

/* coloring parameters */
#define R_U	-256.0
#define R_V	 256.0
#define R_C	 256.0
#define G_U	   0.0
#define G_V	1024.0
#define G_C	   0.0
#define B_U	-512.0
#define B_V	   0.0
#define B_C	 512.0

#define SRAND(s)	srand(s)
#define IRAND()		rand()
#define DRAND()		(((double) rand())/((double) RAND_MAX+1.0))

#define ROUND(x)	((int) round(x))
#define CLAMP(x)	(((x)>0xff)?0xff:((x)<0x00)?0x00:(x))

#define alloc_2d_array(n,m,t)	((t **) allocate_2d_array(n,m,sizeof(t)))
#define free_2d_array(p)	deallocate_2d_array((char *)(p))

/* global variables ----------------------------------------------------*/
static double **u = NULL, **v = NULL, **p = NULL, **q = NULL;

/* prototypes ----------------------------------------------------------*/
void  init_status        (void);
void  update_status      (void);
void  draw_image         (window_t *);
bool  esc_is_pushed      (window_t *);
void *allocate_2d_array  (size_t, size_t, size_t);
void  deallocate_2d_array(void *);

/*======================================================================*/
int main(int argc, char **argv)
{
    window_t  w;
    window_t *window = &w;

    if ((u = alloc_2d_array(HEIGHT, WIDTH, double)) == NULL ||
	(v = alloc_2d_array(HEIGHT, WIDTH, double)) == NULL ||
	(p = alloc_2d_array(HEIGHT, WIDTH, double)) == NULL ||
	(q = alloc_2d_array(HEIGHT, WIDTH, double)) == NULL) {
	perror(argv[0]);
	return EXIT_FAILURE;
    }

    init_status();

    window_open(window, WIDTH, HEIGHT, "Gray-Scott Model");
    draw_image (window);

    do {			/* time steps */
#if TI > 1
	int i;
#pragma omp parallel private(i)
	for (i = 0; i < TI; i++)
	    update_status();
#else
#pragma omp parallel
	update_status();
#endif
	draw_image(window);
	usleep((unsigned int) (0.05 * 1E6));	/* sleep 0.05sec. */
    } while (!esc_is_pushed(window));

    window_close(window);

    free_2d_array(q);
    free_2d_array(p);
    free_2d_array(v);
    free_2d_array(u);

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
void init_status(void)
{				/* setup initial status.                */
    int i, j, di, dj;

    SRAND((int) time(NULL));	/* initialize RNG seed. */

#pragma omp parallel for private(i,j)
    for (j = 0; j < HEIGHT; j++)
	for (i = 0; i < WIDTH; i++)	/* stable status */
	    u[j][i] = US, v[j][i] = VS;

    for (j = 0; j < HEIGHT; j++)
	for (i = 0; i < WIDTH; i++)
	    if (IRAND() % P == 0) {	/* random seed */
		double uu = DRAND(), vv = DRAND();
		for (dj = -R; dj <= R; dj++) {
		    int y = (j + dj + HEIGHT) % HEIGHT;
		    for (di = -R; di <= R; di++) {
			int x = (i + di + WIDTH) % WIDTH;
			if (di * di + dj * dj < R * R)
			    u[y][x] = uu, v[y][x] = vv;
		    }
		}
	    }

    return;
}

/*----------------------------------------------------------------------*/
void update_status(void)
{				/* update status.                       */
    int ii, jj;

#pragma omp for private(ii,jj)
    for (jj = 0; jj < HEIGHT; jj++) {
	int jp = (jj + HEIGHT + 1) % HEIGHT,
	    jm = (jj + HEIGHT - 1) % HEIGHT;
	for (ii = 0; ii < WIDTH; ii++) {	/* p=du/dt, q=dv/dt */
	    int    ip  = (ii + WIDTH + 1) % WIDTH,
		   im  = (ii + WIDTH - 1) % WIDTH;
	    double uvv =      u[jj][ii] * v[jj][ii] * v[jj][ii];
	    p[jj][ii] = DU * (u[jj][ip] + u[jj][im] +
			      u[jp][ii] + u[jm][ii] - 4.0 * u[jj][ii]) -
			uvv +  F * (1.0 - u[jj][ii]);
	    q[jj][ii] = DV * (v[jj][ip] + v[jj][im] +
			      v[jp][ii] + v[jm][ii] - 4.0 * v[jj][ii]) +
			uvv -   (F + K) * v[jj][ii] ;
	}
    }

#pragma omp for private(ii,jj)
    for (jj = 0; jj < HEIGHT; jj++)
	for (ii = 0; ii < WIDTH; ii++) {	/* update status: Euler method */
	    u[jj][ii] += DT * p[jj][ii];
	    v[jj][ii] += DT * q[jj][ii];
	}

    return;
}

/*----------------------------------------------------------------------*/
void draw_image(window_t *window)
{				/* update graphics on the window.       */
    int i, j;

#pragma omp parallel for private(i,j)
    for (j = 0; j < HEIGHT; j++)
	for (i = 0; i < WIDTH; i++) {
	    pixel_t pixel =
		pixel_set_rgb(CLAMP(ROUND(R_U * u[j][i] + R_V * v[j][i] + R_C)),
			      CLAMP(ROUND(G_U * u[j][i] + G_V * v[j][i] + G_C)),
			      CLAMP(ROUND(B_U * u[j][i] + B_V * v[j][i] + B_C)));
	    window_put_pixel(window, pixel, i, j);
	}

    window_update_image(window);

    return;
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

/*-----------------------------------------------------------------------*/
void deallocate_2d_array(void *p)
{				/* deallocate a 2D array.                */
    char **q;

    if ((q = (char **) p) != NULL) {
	free(q[0]); free(q);
    }

    return;
}

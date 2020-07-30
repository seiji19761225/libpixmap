/*
 * solar.c: solar system simulation
 * (c)2015-2016 Seiji Nishimura
 * $Id: solar.c,v 1.1.1.5 2016/01/20 00:00:00 seiji Exp seiji $
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libpixmap/window.h>
#include <libpixmap/palette.h>

// window size
#define WIDTH		512
#define HEIGHT		512

#define R		10
#define USEC		0.0
#define T_STEP		1.E-2
#define WIN_X(x)	(0.5*WIDTH *(1.0+0.025*(x)))
#define WIN_Y(y)	(0.5*HEIGHT*(1.0-0.025*(y)))

// simulation parameter set
#define N		5
#define SOLAR_MASS	(4.0*M_PI*M_PI)
#define DAYS_PER_YEAR	365.25
#define DT		1.E-5
#define EPS2		1.E-12

#define MALLOC(n,t)	((t *) malloc((n)*sizeof(t)))

typedef struct {
    int n;
    double *mass;
    double *x , *y , *z ;
    double *vx, *vy, *vz;
    double *ax, *ay, *az;
} particle_t;

// prototypes
void   particle_initialize(particle_t *, double);
void   particle_update    (particle_t *, double);
void   particle_update_a  (particle_t *, double);
void   particle_update_v  (particle_t *, double);
void   particle_update_x  (particle_t *, double);
double particle_energy    (particle_t *);
bool   pushed_esc         (window_t   *);

//======================================================================
int main(int argc, char **argv)
{
    int         i_steps   = 1   , n_steps = 0;
    double      usec      = USEC;
    particle_t  p;
    particle_t *particle = &p;
    window_t    w;
    window_t   *window   = &w;
    pixel_t     white    = pixel_set_rgb(0xff, 0xff, 0xff),
	        black    = pixel_set_rgb(0x00, 0x00, 0x00);

    if (argc > 1)
	usec = fabs(atof(argv[1]));

    particle->n = N;
    i_steps     = T_STEP / DT;

    if ((particle->mass = MALLOC(particle->n, double)) == NULL ||
	(particle->x    = MALLOC(particle->n, double)) == NULL ||
	(particle->y    = MALLOC(particle->n, double)) == NULL ||
	(particle->z    = MALLOC(particle->n, double)) == NULL ||
	(particle->vx   = MALLOC(particle->n, double)) == NULL ||
	(particle->vy   = MALLOC(particle->n, double)) == NULL ||
	(particle->vz   = MALLOC(particle->n, double)) == NULL ||
	(particle->ax   = MALLOC(particle->n, double)) == NULL ||
	(particle->ay   = MALLOC(particle->n, double)) == NULL ||
	(particle->az   = MALLOC(particle->n, double)) == NULL) {
	perror(argv[0]);
	return EXIT_FAILURE;
    }

    particle_initialize(particle, DT);

    window_open(window, WIDTH, HEIGHT, "Solar System");

    do {
	int i;
	char buf[256];
        // time integration
#pragma omp parallel private(i)
	for (i = 0; i < i_steps; i++)
	    particle_update(particle, DT);
        // visualization
	window_clear_image (window, black);
	for (i = 0; i < particle->n; i++) {
	    int x = WIN_X(particle->x[i]),
		y = WIN_Y(particle->y[i]);
	    pixel_t pixel = palette(IDL2_BLUE_RED, 0, particle->n, particle->n - i);
	    window_fill_ellipse(window, pixel, x, y, R, R);
	}
	snprintf(buf, sizeof(buf), "T=%.2f E=%.5f",
			++n_steps * T_STEP, particle_energy(particle));
	window_draw_string (window, white, 5, 5, buf);
	window_update_image(window);
        // delay
	if (usec >  0.0 &&
	    usec <= 1.0)
	    usleep(usec * 1E6);
    } while (!pushed_esc(window));

    window_close(window);

    free(particle->az  );
    free(particle->ay  );
    free(particle->ax  );
    free(particle->vz  );
    free(particle->vy  );
    free(particle->vx  );
    free(particle->z   );
    free(particle->y   );
    free(particle->x   );
    free(particle->mass);

    return EXIT_SUCCESS;
}

//----------------------------------------------------------------------
void particle_initialize(particle_t *particle, double dt)
{
    int i;
    double px, py, pz;

    // 0:Sun
    particle->mass[0] = SOLAR_MASS;
    particle->x   [0] = 0.0;
    particle->y   [0] = 0.0;
    particle->z   [0] = 0.0;
    particle->vx  [0] = 0.0;
    particle->vy  [0] = 0.0;
    particle->vz  [0] = 0.0;

    // 1:Jupiter
    particle->mass[1] =  9.54791938424326609e-04 * SOLAR_MASS;
    particle->x   [1] =  4.84143144246472090e+00;
    particle->y   [1] = -1.16032004402742839e+00;
    particle->z   [1] = -1.03622044471123109e-01;
    particle->vx  [1] =  1.66007664274403694e-03 * DAYS_PER_YEAR;
    particle->vy  [1] =  7.69901118419740425e-03 * DAYS_PER_YEAR;
    particle->vz  [1] = -6.90460016972063023e-05 * DAYS_PER_YEAR;

    // 2:Saturn
    particle->mass[2] =  2.85885980666130812e-04 * SOLAR_MASS;
    particle->x   [2] =  8.34336671824457987e+00;
    particle->y   [2] =  4.12479856412430479e+00;
    particle->z   [2] = -4.03523417114321381e-01;
    particle->vx  [2] = -2.76742510726862411e-03 * DAYS_PER_YEAR;
    particle->vy  [2] =  4.99852801234917238e-03 * DAYS_PER_YEAR;
    particle->vz  [2] =  2.30417297573763929e-05 * DAYS_PER_YEAR;

    // 3:Uranus
    particle->mass[3] =  4.36624404335156298e-05 * SOLAR_MASS;
    particle->x   [3] =  1.28943695621391310e+01;
    particle->y   [3] = -1.51111514016986312e+01;
    particle->z   [3] = -2.23307578892655734e-01;
    particle->vx  [3] =  2.96460137564761618e-03 * DAYS_PER_YEAR;
    particle->vy  [3] =  2.37847173959480950e-03 * DAYS_PER_YEAR;
    particle->vz  [3] = -2.96589568540237556e-05 * DAYS_PER_YEAR;

    // 4:Neptune
    particle->mass[4] =  5.15138902046611451e-05 * SOLAR_MASS;
    particle->x   [4] =  1.53796971148509165e+01;
    particle->y   [4] = -2.59193146099879641e+01;
    particle->z   [4] =  1.79258772950371181e-01;
    particle->vx  [4] =  2.68067772490389322e-03 * DAYS_PER_YEAR;
    particle->vy  [4] =  1.62824170038242295e-03 * DAYS_PER_YEAR;
    particle->vz  [4] = -9.51592254519715870e-05 * DAYS_PER_YEAR;

    px = 0.0;
    py = 0.0;
    pz = 0.0;
    for (i = 0; i < particle->n; i++) {
	px += particle->vx[i] * particle->mass[i];
	py += particle->vy[i] * particle->mass[i];
	pz += particle->vz[i] * particle->mass[i];
    }

    // initial momentum offset of the Sun
    particle->vx[0] = -px / SOLAR_MASS;
    particle->vy[0] = -py / SOLAR_MASS;
    particle->vz[0] = -pz / SOLAR_MASS;

    // leapfrog
#pragma omp parallel
    particle_update_a(particle, dt);
    particle_update_v(particle, dt * 0.5);
    particle_update_x(particle, dt);

    return;
}

//----------------------------------------------------------------------
void particle_update(particle_t *particle, double dt)
{
    particle_update_a(particle, dt);
    particle_update_v(particle, dt);
    particle_update_x(particle, dt);

    return;
}

//----------------------------------------------------------------------
void particle_update_a(particle_t *particle, double dt)
{
    int i, j;

#pragma omp for
    for (i = 0; i < particle->n; i++) {
	double ax = 0.0,
	       ay = 0.0,
	       az = 0.0;
#pragma ivdep
	for (j = 0; j < particle->n; j++)
	    if (i != j) {
		double r3inv;
		double dx = particle->x[i] - particle->x[j],
		       dy = particle->y[i] - particle->y[j],
		       dz = particle->z[i] - particle->z[j];
		double r2 = dx * dx + dy * dy + dz * dz;
#ifdef EPS2
		r2   += EPS2;	// softening
#endif
		r3inv = 1.0 / (r2 * sqrt(r2));
		dx   *= r3inv;
		dy   *= r3inv;
		dz   *= r3inv;
		ax   -= particle->mass[j] * dx;
		ay   -= particle->mass[j] * dy;
		az   -= particle->mass[j] * dz;
	    }
	particle->ax[i] = ax;
	particle->ay[i] = ay;
	particle->az[i] = az;
    }

    return;
}

//----------------------------------------------------------------------
void particle_update_v(particle_t *particle, double dt)
{
    int i;

#pragma omp for
    for (i = 0; i < particle->n; i++) {
	particle->vx[i] += dt * particle->ax[i];
	particle->vy[i] += dt * particle->ay[i];
	particle->vz[i] += dt * particle->az[i];
    }

    return;
}

//----------------------------------------------------------------------
void particle_update_x(particle_t *particle, double dt)
{
    int i;

#pragma omp for
    for (i = 0; i < particle->n; i++) {
	particle->x[i] += dt * particle->vx[i];
	particle->y[i] += dt * particle->vy[i];
	particle->z[i] += dt * particle->vz[i];
    }

    return;
}

//----------------------------------------------------------------------
double particle_energy(particle_t *particle)
{
    int i, j;
    double energy_k = 0.0,
	   energy_p = 0.0;

    // kinetic energy: e=0.5*m*v^2
    for (i = 0; i < particle->n; i++) {
	double v2 = particle->vx[i] * particle->vx  [i] +
		    particle->vy[i] * particle->vy  [i] +
		    particle->vz[i] * particle->vz  [i];
	energy_k += 0.5 * v2 * particle->mass[i];
    }

    // potential energy: e=-m*g*h
#pragma omp parallel for private(i,j) reduction(+:energy_p) schedule(static,1)
    for (i = 0; i < particle->n; i++)
#pragma ivdep
	for (j = i + 1; j < particle->n; j++) {
	    double dx = particle->x[i] - particle->x[j],
		   dy = particle->y[i] - particle->y[j],
		   dz = particle->z[i] - particle->z[j];
	    double r2 = dx * dx + dy * dy + dz * dz;
#ifdef EPS2
	    r2 += EPS2;
#endif
	    energy_p -= particle->mass[i] * particle->mass[j] / sqrt(r2);
	}

    return energy_k + energy_p;
}

//----------------------------------------------------------------------
bool pushed_esc(window_t *window)
{
    int device, code, x, y;

    do {
	window_get_input(window, false, &device, &code, &x, &y);
	if (device == WD_KeyBoard &&
	    code   == WK_ESC)
	    return true;
    } while (device != WD_Null);

    return false;
}

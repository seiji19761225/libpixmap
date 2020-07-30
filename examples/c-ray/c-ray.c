/*
 * c-ray.c
 * (c)2014-2016 Seiji Nishimura
 * $Id: c-ray.c,v 1.1.1.4 2016/02/16 00:00:00 seiji Exp seiji $
 */
/* c-ray - a simple raytracing filter.
 * Copyright (C) 2006 John Tsiombikas <nuclear@siggraph.org>
 *
 * You are free to use, modify and redistribute this program under the
 * terms of the GNU General Public License v2 or (at your option) later.
 * see "http://www.gnu.org/licenses/gpl.txt" for details.
 * ---------------------------------------------------------------------
 * Usage:
 *   compile:  cc -o c-ray c-ray.c -lm
 *   run:      cat scene | ./c-ray >foo.ppm
 *   enjoy:    display foo.ppm (with imagemagick)
 *      or:    imgview foo.ppm (on IRIX)
 * ---------------------------------------------------------------------
 * Scene file format:
 *   # sphere (many)
 *   s  x y z  rad   r g b   shininess   reflectivity
 *   # light (many)
 *   l  x y z
 *   # camera (one)
 *   c  x y z  fov   tx ty tz
 * ---------------------------------------------------------------------
 */

#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <libpixmap/pixmap.h>

#define NRAN		(0x01<<16)
#define MASK		(NRAN-1)

#define MIN_AA_SAMPLES	(0x01<<4)
#define MAX_AA_SAMPLES	NRAN

#define MAX_LIGHTS	16		/* maximum number of lights */
#define RAY_MAG		1000.0		/* trace rays of this magnitude */
#define MAX_RAY_DEPTH	5		/* raytrace recursion limit */
#ifdef M_PI_4
#define FOV		M_PI_4		/* field of view in rads (pi/4) */
#else
#define FOV		0.78539816339744830962
#endif
#define HALF_FOV	(FOV*0.5)
#define ERR_MARGIN	1e-6		/* an arbitrary error margin to avoid surface acne */

/* some helpful macros... */
#define SQ(x)		((x)*(x))
#define ROUND(x)	((int) ((x)+0.5))
#define MAX(a,b)	((a)>(b)?(a):(b))
#define MIN(a,b)	((a)<(b)?(a):(b))
#define DOT(a,b)	((a).x*(b).x+(a).y*(b).y+(a).z*(b).z)
#define NORMALIZE(a)	\
{\
    double len = sqrt(DOT(a, a));\
    (a).x /= len; (a).y /= len; (a).z /= len;\
}

#define SAME_COLOR(p,q)	(3*abs(pixel_get_r(p)-pixel_get_r(q))+\
			 6*abs(pixel_get_g(p)-pixel_get_g(q))+\
			 1*abs(pixel_get_b(p)-pixel_get_b(q))<20)

typedef struct vec3 {
    double x, y, z;
} vec3_t;

typedef struct ray {
    vec3_t orig, dir;
} ray_t;

typedef struct material {
    vec3_t col;		/* color */
    double spow;	/* specular power */
    double refl;	/* reflection intensity */
} material_t;

typedef struct sphere {
    vec3_t pos;
    double rad;
    material_t mat;
    struct sphere *next;
} sphere_t;

typedef struct spoint {
    vec3_t pos, normal, vref;	/* position, normal and view reflection */
    double dist;		/* parametric distance of intersection along the ray */
} spoint_t;

typedef struct camera {
    vec3_t pos, targ;
    double fov;
} camera_t;

/* global state */
int xres = 800, yres = 600, lnum = 0;
double aspect, urand_x[NRAN], urand_y[NRAN];
sphere_t *obj_list = NULL;
vec3_t lights[MAX_LIGHTS];
camera_t cam;

const char *usage = {
    "Usage: c-ray [options] [infile [outfile]]\n"
    "  Reads a scene file from stdin, writes the image to stdout, and stats to stderr.\n\n"
    "Options:\n"
    "  -s WxH     where W is the width and H the height of the image\n"
    "  -r <rays>  shoot <rays> rays per pixel (antialiasing)\n"
    "  -i <file>  read from <file> instead of stdin\n"
    "  -o <file>  write to <file> instead of stdout\n"
    "  -h         this help screen\n\n"
};

/* prototypes */
void   adaptive_aalias(pixmap_t *, pixmap_t *, int);
void   multi_sampling (pixmap_t *, pixmap_t *, int);
void   edge_image     (pixmap_t *, pixmap_t *, int);
int    detect_edge    (pixmap_t *, pixel_t  *, int, int);
vec3_t trace          (ray_t, int);
vec3_t shade          (sphere_t *, spoint_t *, int);
vec3_t reflect        (vec3_t, vec3_t);
vec3_t cross_product  (vec3_t, vec3_t);
ray_t  get_primary_ray(int, int, int);
vec3_t get_sample_pos (int, int, int);
vec3_t jitter         (int, int, int);
int    ray_sphere     (const sphere_t *, ray_t, spoint_t *);
void   load_scene     (FILE *);
unsigned long get_msec(void);

/*====================================================================*/
int main(int argc, char **argv)
{
    int i, option, rays_per_pixel = -1;
    unsigned long rend_time, start_time;
    pixmap_t pixmap, sketch;
    const char *optstring = "hi:o:r:s:";
    FILE *infile = stdin, *outfile = stdout;
    void (*render)(pixmap_t *, pixmap_t *, int);

    while ((option = getopt(argc, argv, optstring)) != -1) {
	char *sep;
	switch (option) {
	case ('h'):
	    fputs(usage, stderr);
	    return EXIT_SUCCESS;
	case ('i'):
	    if ( infile  != stdin ) fclose(infile );
	    if ((infile   = fopen(optarg, "r" )) == NULL) {
		perror(optarg);
		return EXIT_FAILURE;
	    }
	    break;
	case ('o'):
	    if ( outfile != stdout) fclose(outfile);
	    if ((outfile = fopen(optarg, "wb")) == NULL) {
		perror(optarg);
		return EXIT_FAILURE;
	    }
	    break;
	case ('r'):
	    if (!isdigit(*optarg)) {
		fputs("-r must be followed by a number (rays per pixel)\n",
		      stderr);
		return EXIT_FAILURE;
	    }
	    rays_per_pixel = atoi(optarg);
	    break;
	case ('s'):
	    if (!isdigit(*optarg) || (sep = strchr(optarg, 'x')) == NULL ||
		!isdigit(*(sep + 1))) {
		fputs("-s must be followed by something like \"640x480\"\n",
		      stderr);
		return EXIT_FAILURE;
	    }
	    xres = atoi(optarg );
	    yres = atoi(sep + 1);
	    break;
	case ('?'):
	default:
	    fputs(usage, stderr);
	    return EXIT_FAILURE;
	}
    }

    if (optind < argc) {
	if (optind != argc - 1 && optind != argc - 2) {
	    fputs(usage, stderr);
	    return EXIT_FAILURE;
	}
	if ( infile != stdin) fclose(infile);
	if ((infile  = fopen(argv[optind], "r")) == NULL) {
	    perror(argv[optind]);
	    return EXIT_FAILURE;
	}
	if (++optind < argc) {
	    if ( outfile != stdout) fclose(outfile);
	    if ((outfile  = fopen(argv[optind], "wb")) == NULL) {
		perror(argv[optind]);
		return EXIT_FAILURE;
	    }
	}
    }

    aspect = (double) xres / yres;

    switch (rays_per_pixel) {
    case (-1): render = adaptive_aalias; break;	/* specified no -r option. */
    case ( 0): render = edge_image     ; break;
    default  : render = multi_sampling ; break;
    }

    load_scene(infile);

    srand((unsigned int) time(NULL));

    /* initialize the random number tables for the jitter */
    for (i = 0; i < NRAN; i++) {
	urand_x[i] = (double) rand() / (RAND_MAX + 1.0);
	urand_y[i] = (double) rand() / (RAND_MAX + 1.0);
    }

    pixmap_create(&pixmap, xres, yres);
    pixmap_create(&sketch, xres, yres);

    start_time = get_msec();
#pragma omp parallel
    render(&pixmap, &sketch, rays_per_pixel);
    rend_time  = get_msec() - start_time;

    /* output statistics to stderr */
    fprintf(stderr, "Rendering took: %lu seconds (%lu milliseconds)\n",
	    (unsigned long) round(rend_time / 1000.0), rend_time);

    /* output the image */
    pixmap_write_pnmfp(&pixmap, outfile);

    pixmap_destroy(&sketch);
    pixmap_destroy(&pixmap);

    /* free allocated memory */
    while (obj_list != NULL) {
	sphere_t *sp = obj_list->next;
	free(obj_list);
	obj_list = sp;
    }

    if (infile  != stdin ) fclose(infile );
    if (outfile != stdout) fclose(outfile);

    return EXIT_SUCCESS;
}

/*--------------------------------------------------------------------*/
/* render a frame of xres/yres dimensions into the provided framebuffer */
void adaptive_aalias(pixmap_t *pixmap, pixmap_t *sketch, int samples)
{
    int i, j;
    vec3_t col;
    pixel_t pixel;

#pragma omp for schedule(static,1) collapse(2)
    for (j = 0; j < yres; j++)
	for (i = 0; i < xres; i++) {
	    col = trace(get_primary_ray(i, j, 0), 0);

	    pixel = pixel_set_rgb(ROUND(255.0 * MIN(1.0, col.x)),
				  ROUND(255.0 * MIN(1.0, col.y)),
				  ROUND(255.0 * MIN(1.0, col.z)));
	    pixmap_put_pixel(sketch, pixel, i, j);
	}

    /* for each subpixel, trace a ray through the scene, accumulate the
     * colors of the subpixels of each pixel, then pack the color and
     * put it into the framebuffer.
     */
#pragma omp for nowait schedule(static,1) collapse(2)
    for (j = 0; j < yres; j++)
	for (i = 0; i < xres; i++) {
	    /* adaptive anti-aliasing for edge */
	    if (detect_edge(sketch, &pixel, i, j)) {
		int l, m, n;
		double r, g, b, factor;
		pixel_t avg = pixel;

		r = (double) pixel_get_r(pixel) / 255.0;
		g = (double) pixel_get_g(pixel) / 255.0;
		b = (double) pixel_get_b(pixel) / 255.0;
		m = 1; n = MIN_AA_SAMPLES;

		do {
		    pixel  = avg;
		    factor = 1.0 / (double) n;
		    for (l = m; l < n; l++) {	/* Monte-Carlo integration */
			col = trace(get_primary_ray(i, j, l), 0);
			r  += col.x;
			g  += col.y;
			b  += col.z;
		    }
		    avg = pixel_set_rgb(ROUND(255.0 * MIN(1.0, r * factor)),
					ROUND(255.0 * MIN(1.0, g * factor)),
					ROUND(255.0 * MIN(1.0, b * factor)));
		} while (!SAME_COLOR(pixel, avg) &&
			(n = (m = n) << 0x01) <= MAX_AA_SAMPLES);
		pixel = avg;
	    }
	    pixmap_put_pixel(pixmap, pixel, i, j);
	}

    return;
}

/*--------------------------------------------------------------------*/
/* render a frame of xres/yres dimensions into the provided framebuffer */
void multi_sampling(pixmap_t *pixmap, pixmap_t *sketch, int samples)
{
    int i, j;
    double rcp_samples;
    pixel_t pixel;
    vec3_t col;

    rcp_samples = 1.0 / (double) samples;

#pragma omp for schedule(static,1) collapse(2)
    for (j = 0; j < yres; j++)
	for (i = 0; i < xres; i++) {
	    col = trace(get_primary_ray(i, j, 0), 0);

	    pixel = pixel_set_rgb(ROUND(255.0 * MIN(1.0, col.x)),
				  ROUND(255.0 * MIN(1.0, col.y)),
				  ROUND(255.0 * MIN(1.0, col.z)));
	    pixmap_put_pixel(sketch, pixel, i, j);
	}

    /* for each subpixel, trace a ray through the scene, accumulate the
     * colors of the subpixels of each pixel, then pack the color and
     * put it into the framebuffer.
     */
#pragma omp for nowait schedule(static,1) collapse(2)
    for (j = 0; j < yres; j++)
	for (i = 0; i < xres; i++) {
	    /* anti-aliasing for edge */
	    if (detect_edge(sketch, &pixel, i, j)) {
		int s;
		double r, g, b;

		r = (double) pixel_get_r(pixel) / 255.0;
		g = (double) pixel_get_g(pixel) / 255.0;
		b = (double) pixel_get_b(pixel) / 255.0;

		for (s = 1; s < samples; s++) {	/* Monte-Carlo integration */
		    col = trace(get_primary_ray(i, j, s), 0);
		    r  += col.x;
		    g  += col.y;
		    b  += col.z;
		}
		pixel = pixel_set_rgb(ROUND(255.0 * MIN(1.0, r * rcp_samples)),
				      ROUND(255.0 * MIN(1.0, g * rcp_samples)),
				      ROUND(255.0 * MIN(1.0, b * rcp_samples)));
	    }
	    pixmap_put_pixel(pixmap, pixel, i, j);
	}

    return;
}

/*--------------------------------------------------------------------*/
/* render a frame of xres/yres dimensions into the provided framebuffer */
void edge_image(pixmap_t *pixmap, pixmap_t *sketch, int samples)
{
    int i, j;
    vec3_t col;
    pixel_t pixel;
    const pixel_t black = pixel_set_rgb(0x00, 0x00, 0x00),
		  white = pixel_set_rgb(0xff, 0xff, 0xff);

#pragma omp for schedule(static,1) collapse(2)
    for (j = 0; j < yres; j++)
	for (i = 0; i < xres; i++) {
	    col = trace(get_primary_ray(i, j, 0), 0);

	    pixel = pixel_set_rgb(ROUND(255.0 * MIN(1.0, col.x)),
				  ROUND(255.0 * MIN(1.0, col.y)),
				  ROUND(255.0 * MIN(1.0, col.z)));
	    pixmap_put_pixel(sketch, pixel, i, j);
	}

#pragma omp for nowait schedule(static,1) collapse(2)
    for (j = 0; j < yres; j++)
	for (i = 0; i < xres; i++) {
	    int edge = detect_edge(sketch, &pixel, i, j);

	 /* pixel = edge ? white : pixel; */
	    pixel = edge ? white : black;

	    pixmap_put_pixel(pixmap, pixel, i, j);
	}

    return;
}

/*--------------------------------------------------------------------*/
/* detect whether current pixel is edge or not. */
int detect_edge(pixmap_t *pixmap, pixel_t *pixel, int x, int y)
{
    int  i, j;
    pixel_t p;

    pixmap_get_pixel(pixmap, pixel, x, y);

    for (j = MAX(0, y - 1); j <= MIN(yres - 1, y + 1); j++)
	for (i = MAX(0, x - 1); i <= MIN(xres - 1, x + 1); i++)
	    if (i != x || j != y) {
		pixmap_get_pixel(pixmap, &p, i, j);
		if (!SAME_COLOR(*pixel, p))
		    return 1;	/* current pixel is edge.     */
	    }

    return 0;			/* current pixel is NOT edge. */
}

/*--------------------------------------------------------------------*/
/* trace a ray throught the scene recursively (the recursion happens through
 * shade() to calculate reflection rays if necessary).
 */
vec3_t trace(ray_t ray, int depth)
{
    vec3_t col = { 0.0, 0.0, 0.0 };
    spoint_t sp, nearest_sp;
    sphere_t *nearest_obj = NULL, *iter = obj_list->next;

    /* if we reached the recursion limit, bail out */
    if (depth >= MAX_RAY_DEPTH) return col;

    /* find the nearest intersection ... */
    while (iter != NULL) {
	if (ray_sphere(iter, ray, &sp))
	    if (nearest_obj == NULL || sp.dist < nearest_sp.dist) {
		nearest_obj = iter;
		nearest_sp  = sp;
	    }
	iter = iter->next;
    }

    /* and perform shading calculations as needed by calling shade() */
    if (nearest_obj != NULL)
	col = shade(nearest_obj, &nearest_sp, depth);

    return col;
}

/*--------------------------------------------------------------------*/
/* Calculates direct illumination with the phong reflectance model.
 * Also handles reflections by calling trace again, if necessary.
 */
vec3_t shade(sphere_t *obj, spoint_t *sp, int depth)
{
    int i;
    vec3_t col = { 0.0, 0.0, 0.0 };

    /* for all lights ... */
    for (i = 0; i < lnum; i++) {
	int in_shadow = 0;
	double ispec, idiff;
	vec3_t ldir;
	ray_t shadow_ray;
	sphere_t *iter = obj_list;

	ldir.x = lights[i].x - sp->pos.x;
	ldir.y = lights[i].y - sp->pos.y;
	ldir.z = lights[i].z - sp->pos.z;

	shadow_ray.orig = sp->pos;
	shadow_ray.dir  = ldir;

	/* shoot shadow rays to determine if we have a line of sight with the light */
	while ((iter = iter->next) != NULL)
	    if (ray_sphere(iter, shadow_ray, NULL)) {
		in_shadow = 1;
		break;
	    }

	/* and if we're not in shadow, calculate direct illumination with the phong model. */
	if (!in_shadow) {
	    NORMALIZE(ldir);

	    idiff = MAX(DOT(sp->normal, ldir), 0.0);
	    ispec = (obj->mat.spow > 0.0) ? 
		pow(MAX(DOT(sp->vref, ldir), 0.0), obj->mat.spow) : 0.0;

	    col.x += idiff * obj->mat.col.x + ispec;
	    col.y += idiff * obj->mat.col.y + ispec;
	    col.z += idiff * obj->mat.col.z + ispec;
	}
    }

    /* Also, if the object is reflective, spawn a reflection ray, and call trace()
     * to calculate the light arriving from the mirror direction.
     */
    if (obj->mat.refl > 0.0) {
	ray_t ray;
	vec3_t rcol;

	ray.orig = sp->pos;
	ray.dir  = sp->vref;
	ray.dir.x *= RAY_MAG;
	ray.dir.y *= RAY_MAG;
	ray.dir.z *= RAY_MAG;

	rcol = trace(ray, depth + 1);
	col.x += rcol.x * obj->mat.refl;
	col.y += rcol.y * obj->mat.refl;
	col.z += rcol.z * obj->mat.refl;
    }

    return col;
}

/*--------------------------------------------------------------------*/
/* calculate reflection vector */
vec3_t reflect(vec3_t v, vec3_t n)
{
    vec3_t res;
    double dot = v.x * n.x + v.y * n.y + v.z * n.z;

    res.x = -(2.0 * dot * n.x - v.x);
    res.y = -(2.0 * dot * n.y - v.y);
    res.z = -(2.0 * dot * n.z - v.z);

    return res;
}

/*--------------------------------------------------------------------*/
vec3_t cross_product(vec3_t v1, vec3_t v2)
{
    vec3_t res;

    res.x = v1.y * v2.z - v1.z * v2.y;
    res.y = v1.z * v2.x - v1.x * v2.z;
    res.z = v1.x * v2.y - v1.y * v2.x;

    return res;
}

/*--------------------------------------------------------------------*/
/* determine the primary ray corresponding to the specified pixel (x, y) */
ray_t get_primary_ray(int x, int y, int sample)
{
    ray_t ray;
    double m[3][3];
    vec3_t i, j = { 0.0, 1.0, 0.0 }, k, dir, orig, foo;

    k.x = cam.targ.x - cam.pos.x;
    k.y = cam.targ.y - cam.pos.y;
    k.z = cam.targ.z - cam.pos.z;
    NORMALIZE(k);

    i = cross_product(j, k);
    j = cross_product(k, i);
    m[0][0] = i.x; m[0][1] = j.x; m[0][2] = k.x;
    m[1][0] = i.y; m[1][1] = j.y; m[1][2] = k.y;
    m[2][0] = i.z; m[2][1] = j.z; m[2][2] = k.z;

    ray.orig.x = ray.orig.y = ray.orig.z = 0.0;
    ray.dir    = get_sample_pos(x, y, sample);
    ray.dir.z  = 1.0 / HALF_FOV;
    ray.dir.x *= RAY_MAG;
    ray.dir.y *= RAY_MAG;
    ray.dir.z *= RAY_MAG;

    dir.x = ray.dir.x + ray.orig.x;
    dir.y = ray.dir.y + ray.orig.y;
    dir.z = ray.dir.z + ray.orig.z;
    foo.x = dir.x * m[0][0] + dir.y * m[0][1] + dir.z * m[0][2];
    foo.y = dir.x * m[1][0] + dir.y * m[1][1] + dir.z * m[1][2];
    foo.z = dir.x * m[2][0] + dir.y * m[2][1] + dir.z * m[2][2];

    orig.x = ray.orig.x * m[0][0] + ray.orig.y * m[0][1] +
	     ray.orig.z * m[0][2] + cam.pos.x;
    orig.y = ray.orig.x * m[1][0] + ray.orig.y * m[1][1] +
	     ray.orig.z * m[1][2] + cam.pos.y;
    orig.z = ray.orig.x * m[2][0] + ray.orig.y * m[2][1] +
	     ray.orig.z * m[2][2] + cam.pos.z;

    ray.orig  = orig;
    ray.dir.x = foo.x + orig.x;
    ray.dir.y = foo.y + orig.y;
    ray.dir.z = foo.z + orig.z;

    return ray;
}


/*--------------------------------------------------------------------*/
vec3_t get_sample_pos(int x, int y, int sample)
{
    vec3_t pt;
    static double sf = 0.0;

#pragma omp critical(sf_in_get_sample_pos)
    if (sf == 0.0)
	sf =  1.0 / (double) xres;

    pt.x =   ((double) x / (double) xres) - 0.5;
    pt.y = -(((double) y / (double) yres) - 0.65) / aspect;

    if (sample) {
	vec3_t jt = jitter(x, y, sample);

	pt.x += jt.x * sf;
	pt.y += jt.y * sf;
    }

    return pt;
}

/*--------------------------------------------------------------------*/
/* jitter function */
vec3_t jitter(int x, int y, int s)
{
    vec3_t pt;

    pt.x = urand_x[s & MASK];
    pt.y = urand_y[s & MASK];

    return pt;
}

/*--------------------------------------------------------------------*/
/* Calculate ray-sphere intersection, and return {1, 0} to signify hit or no hit.
 * Also the surface point parameters like position, normal, etc are returned through
 * the sp pointer if it is not NULL.
 */
int ray_sphere(const sphere_t *sph, ray_t ray, spoint_t *sp)
{
    double a, b, c, d, sqrt_d, t1, t2;

    a = SQ(ray.dir.x) + SQ(ray.dir.y) + SQ(ray.dir.z);
    b = 2.0 * ray.dir.x * (ray.orig.x - sph->pos.x) +
	2.0 * ray.dir.y * (ray.orig.y - sph->pos.y) +
	2.0 * ray.dir.z * (ray.orig.z - sph->pos.z);
    c = SQ(sph->pos.x) + SQ(sph->pos.y) + SQ(sph->pos.z) +
	SQ(ray.orig.x) + SQ(ray.orig.y) + SQ(ray.orig.z) +
	2.0 * (-sph->pos.x * ray.orig.x  - sph->pos.y * ray.orig.y -
	        sph->pos.z * ray.orig.z) - SQ(sph->rad);

    if ((d = SQ(b) - 4.0 * a * c) < 0.0)
	return 0;

    sqrt_d = sqrt(d);
    t1 = (-b + sqrt_d) / (2.0 * a);
    t2 = (-b - sqrt_d) / (2.0 * a);

    if ((t1 < ERR_MARGIN && t2 < ERR_MARGIN) || (t1 > 1.0 && t2 > 1.0))
	return 0;

    if (sp != NULL) {
	if (t1 < ERR_MARGIN)   t1 = t2;
	if (t2 < ERR_MARGIN)   t2 = t1;
	sp->dist = (t1 < t2) ? t1 : t2;

	sp->pos.x = ray.orig.x + ray.dir.x * sp->dist;
	sp->pos.y = ray.orig.y + ray.dir.y * sp->dist;
	sp->pos.z = ray.orig.z + ray.dir.z * sp->dist;

	sp->normal.x = (sp->pos.x - sph->pos.x) / sph->rad;
	sp->normal.y = (sp->pos.y - sph->pos.y) / sph->rad;
	sp->normal.z = (sp->pos.z - sph->pos.z) / sph->rad;

	sp->vref = reflect(ray.dir, sp->normal);
	NORMALIZE(sp->vref);
    }

    return 1;
}

/*--------------------------------------------------------------------*/
/* Load the scene from an extremely simple scene description file */
#define DELIM	" \t\n"
void load_scene(FILE *fp)
{
    char *ptr, type, line[256];

    if (obj_list == NULL) {
	if ((obj_list = malloc(sizeof(sphere_t))) == NULL) {
	    perror(__func__);
	    exit(EXIT_FAILURE);
	}
	obj_list->next = NULL;
    }

    while ((ptr = fgets(line, sizeof(line), fp)) != NULL) {
	int i;
	vec3_t pos, col;
	double rad, spow, refl;

	while (*ptr == ' ' || *ptr == '\t')         ptr++;
	if    (*ptr == '#' || *ptr == '\n')      continue;

	for (i = 0; ptr[i] != '\0'; i++)
	    ptr[i] = tolower(ptr[i]);

	if ((ptr = strtok(line, DELIM)) == NULL) continue; type  = *ptr;
	if ((ptr = strtok(NULL, DELIM)) == NULL) continue; pos.x = atof(ptr);
	if ((ptr = strtok(NULL, DELIM)) == NULL) continue; pos.y = atof(ptr);
	if ((ptr = strtok(NULL, DELIM)) == NULL) continue; pos.z = atof(ptr);

	if (type == 'l') {
	    if (lnum < MAX_LIGHTS) lights[lnum++] = pos;
	    continue;
	}

	if ((ptr = strtok(NULL, DELIM)) == NULL) continue; rad   = atof(ptr);
	if ((ptr = strtok(NULL, DELIM)) == NULL) continue; col.x = atof(ptr);
	if ((ptr = strtok(NULL, DELIM)) == NULL) continue; col.y = atof(ptr);
	if ((ptr = strtok(NULL, DELIM)) == NULL) continue; col.z = atof(ptr);

	if (type == 'c') {
	    cam.pos  = pos;
	    cam.targ = col;
	    cam.fov  = rad;
	    continue;
	}

	if ((ptr = strtok(NULL, DELIM)) == NULL) continue; spow  = atof(ptr);
	if ((ptr = strtok(NULL, DELIM)) == NULL) continue; refl  = atof(ptr);

	if (type == 's') {
	    sphere_t *sph;
	    if ((sph = malloc(sizeof(sphere_t))) == NULL) {
		perror(__func__);
		exit(EXIT_FAILURE);
	    }
	    sph->next = obj_list->next;
	    sph->pos  = pos;
	    sph->rad  = rad;
	    sph->mat.col   = col;
	    sph->mat.spow  = spow;
	    sph->mat.refl  = refl;
	    obj_list->next = sph;
	} else {
	    fprintf(stderr, "unknown type: %c\n", type);
	}
    }

    return;
}

/*--------------------------------------------------------------------*/
/* provide a millisecond-resolution timer for each system */
unsigned long get_msec(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1) {
	perror(__func__);
	exit(EXIT_FAILURE);
    }

    return tv.tv_sec * 1E+3 + tv.tv_usec * 1E-3;
}

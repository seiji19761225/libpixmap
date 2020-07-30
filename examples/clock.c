/*
 * clock.c: a simple digital clock
 * (c)2010-2016 Seiji Nishimura
 * $Id: clock.c,v 1.1.1.4 2016/01/20 00:00:00 seiji Exp seiji $
 */

#include <time.h>
#include <unistd.h>
#include <libpixmap/window.h>

#define MARGIN	3
#define DELAY	0.25
#define WIDTH	(2*MARGIN+FONT_WIDTH*24)	/* strlen(get_clock(buf))==24 */
#define HEIGHT	(2*MARGIN+FONT_HEIGHT)

/* prototypes */
char *get_clock    (char *);
bool  esc_is_pushed(window_t *);

/*======================================================================*/
int main(int argc, char **argv)
{
    char buf[32];		/* must be sizeof(buf)>=26. */
    window_t  w;
    window_t *window = &w;
    const pixel_t black = pixel_set_rgb(0x00, 0x00, 0x00),
		  white = pixel_set_rgb(0xff, 0xff, 0xff);

    window_open(window, WIDTH, HEIGHT, "Digital Clock");

    do {
	window_clear_image (window, black);
	window_draw_string (window, white, MARGIN, MARGIN, get_clock(buf));
	window_update_image(window);
	usleep(1E6 * DELAY);
    } while (!esc_is_pushed(window));

    window_close(window);

    return 0;
}

/*----------------------------------------------------------------------*/
char *get_clock(char *buf)
{				/* get current time info.               */
    char  *sp;
    time_t tm;

    time(&tm);

    for (sp = ctime_r(&tm, buf); *sp != '\0' &&
				 *sp != '\n'; sp++);

    *sp = '\0';

    return buf;
}

/*----------------------------------------------------------------------*/
bool esc_is_pushed(window_t *window)
{				/* detect ESC key input.                */
    int device, code, x, y;

    do {
	window_get_input(window, false, &device, &code, &x, &y);
    } while (device != WD_Null &&
	    (device != WD_KeyBoard  || code != WK_ESC));

    return   device == WD_KeyBoard  && code == WK_ESC;
}

/*
 * colorbar.c: palette module demo
 * (c)2012-2015 Seiji Nishimura
 * $Id: colorbar.c,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <stdio.h>
#include <libpixmap/pixmap.h>
#include <libpixmap/palette.h>

#define TEXT_WIDTH	33
#define BAR_H		(FONT_HEIGHT)
#define SIZE		(FONT_HEIGHT*PALETTE_NTYPES)
#define MARGIN		(FONT_WIDTH *TEXT_WIDTH    )

/*======================================================================*/
int main(void)
{
    int i;
    pixmap_t pixmap;
    const pixel_t white = pixel_set_rgb(0xff, 0xff, 0xff);

    pixmap_create(&pixmap, MARGIN + SIZE, SIZE);

#pragma parallel for private(i)
    for (i = 0; i < PALETTE_NTYPES; i++) {
	int j, id;
	const char *name;
	char buf[TEXT_WIDTH + 1];
	name = palette_search_name(i   );
	id   = palette_search_id  (name);
	snprintf(buf, sizeof(buf), "%-*s(%2d):", TEXT_WIDTH - 5, name, id);
	pixmap_draw_string(&pixmap, white, 0, i * BAR_H, buf);
	for (j = 0; j < SIZE; j++) {
	    pixel_t pixel = palette(id, 0, SIZE - 1, j);
	    pixmap_draw_line(&pixmap, pixel, j + MARGIN, i * BAR_H,
					     j + MARGIN, i * BAR_H + BAR_H - 2);
	}
    }

    pixmap_draw_line(&pixmap, white, MARGIN - 1, 0,
				     MARGIN - 1, SIZE - 1);

    pixmap_write_pnmfile(&pixmap, "colorbar.ppm");
#if 0
    pixmap_write_pnmfile(&pixmap, "colorbar.pgm");
    pixmap_write_pnmfile(&pixmap, "colorbar.pbm");
#endif

    pixmap_destroy(&pixmap);

    return 0;
}

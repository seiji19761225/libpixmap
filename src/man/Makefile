#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# makefile
# $Id: Makefile,v 1.1.1.3 2016/01/20 00:00:00 seiji Exp seiji $
#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
include ../../make.inc

.PHONY: default clean clobber install uninstall
#-----------------------------------------------------------------------
# modules
#........................................................................
# pixmap module (core module)
COREDIR	= pixmap
COREMAN	= \
pixel_blend.l            pixel_get_b.l             pixel_get_g.l            \
pixel_get_r.l            pixel_invert.l            pixel_set_named_color.l  \
pixel_set_rgb.l          pixmap.h.l                pixmap.l                 \
pixmap_blend_image.l     pixmap_blend_subimage.l   pixmap_clear_image.l     \
pixmap_clear_subimage.l  pixmap_copy_image.l       pixmap_copy_subimage.l   \
pixmap_create.l          pixmap_destroy.l          pixmap_draw_arc.l        \
pixmap_draw_arrow.l      pixmap_draw_ellipse.l     pixmap_draw_line.l       \
pixmap_draw_polygon.l    pixmap_draw_string.l      pixmap_fill_arc.l        \
pixmap_fill_ellipse.l    pixmap_fill_polygon.l     pixmap_fill_triangle.l   \
pixmap_get_pixel.l       pixmap_get_size.l         pixmap_intro.l           \
pixmap_invert_image.l    pixmap_invert_subimage.l  pixmap_load_pnmfile.l    \
pixmap_load_pnmfp.l      pixmap_put_pixel.l        pixmap_write_pnmfile.l   \
pixmap_write_pnmfp.l
#........................................................................
# palette module
PALTDIR	= palette
PALTMAN	= \
palette.h.l            palette.l  palette_intro.l  palette_search_id.l  \
palette_search_name.l
#........................................................................
# window module
WINDIR	= window
WINMAN	= \
window.h.l                window.l                window_clear_image.l      \
window_clear_subimage.l   window_close.l          window_discard_inputs.l   \
window_draw_arc.l         window_draw_arrow.l     window_draw_ellipse.l     \
window_draw_line.l        window_draw_polygon.l   window_draw_string.l      \
window_fill_arc.l         window_fill_ellipse.l   window_fill_polygon.l     \
window_fill_triangle.l    window_get_image.l      window_get_input.l        \
window_get_pixel.l        window_get_size.l       window_get_subimage.l     \
window_intro.l            window_invert_image.l   window_invert_subimage.l  \
window_load_pnmfile.l     window_load_pnmfp.l     window_open.l             \
window_put_image.l        window_put_pixel.l      window_put_subimage.l     \
window_query_pointer.l    window_rename.l         window_update_image.l     \
window_update_subimage.l  window_write_pnmfile.l  window_write_pnmfp.l
#-----------------------------------------------------------------------
DIRS	= $(COREDIR) $(PALTDIR)
MANS	= $(COREMAN) $(PALTMAN)
#-----------------------------------------------------------------------
#defaults
PREFIX	= $(shell grep ^PREFIX ../config.mk | tail -1 | awk '{printf $$3;}')
WINSYS	= $(shell grep ^WINSYS ../config.mk | tail -1 | awk '{printf $$3;}')
#.......................................................................
# destination directory
DESTDIR	= $(PREFIX)/$(MANDIR)
#.......................................................................
# modules
ifneq ($(WINSYS),)
ifneq ($(WINSYS),none)
DIRS	+= $(WINDIR)
MANS	+= $(WINMAN)
endif
endif
#-----------------------------------------------------------------------
default:

install:
	mkdir -p $(DESTDIR)/manl
	cd $(COREDIR); $(INSTALL) $(M644) $(strip $(COREMAN)) $(DESTDIR)/manl
	cd $(PALTDIR); $(INSTALL) $(M644) $(strip $(PALTMAN)) $(DESTDIR)/manl
ifneq ($(WINSYS),none)
	cd $(WINDIR) ; $(INSTALL) $(M644) $(strip $(WINMAN))  $(DESTDIR)/manl
endif

uninstall:
	if [ -d $(DESTDIR)/manl ]; then cd $(DESTDIR)/manl; rm -f $(strip $(MANS)); fi

update_db:
	if [ -x "`which mandb      2> /dev/null`" ]; then mandb      -q   $(DESTDIR); fi
	if [ -x "`which makewhatis 2> /dev/null`" ]; then makewhatis -s l $(DESTDIR); fi

clean clobber: uninstall

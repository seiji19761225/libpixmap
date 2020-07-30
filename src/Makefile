#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# makefile
# $Id: Makefile,v 1.1.1.11 2020/07/29 00:00:00 seiji Exp seiji $
#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
include ../make.inc

.PHONY: clean clobber default install uninstall
#------------------------------------------------------------------------
# modules
#........................................................................
# pixmap module (core module)
COREDIR	= pixmap
CORESRC	= \
pixel_blend.c           pixel_invert.c           pixel_set_named_color.c   \
pixmap_abort.c          pixmap_blend_image.c     pixmap_blend_subimage.c   \
pixmap_clear_image.c    pixmap_clear_subimage.c  pixmap_copy_image.c       \
pixmap_copy_subimage.c  pixmap_create.c          pixmap_destroy.c          \
pixmap_draw_arc.c       pixmap_draw_arrow.c      pixmap_draw_ellipse.c     \
pixmap_draw_line.c      pixmap_draw_polygon.c    pixmap_draw_string.c      \
pixmap_draw_triangle.c  pixmap_fill_arc.c        pixmap_fill_ellipse.c     \
pixmap_fill_polygon.c   pixmap_fill_triangle.c   pixmap_get_pixel.c        \
pixmap_get_size.c       pixmap_invert_image.c    pixmap_invert_subimage.c  \
pixmap_load_pnmfile.c   pixmap_load_pnmfp.c      pixmap_put_pixel.c        \
pixmap_write_pnmfile.c
#........................................................................
# palette module
PALTDIR	= palette
PALTSRC	= palette.c       palette_search_id.c       palette_search_name.c
#........................................................................
# window module
WINDIR	= window
WINSRC	= \
window_clear_image.c      window_clear_subimage.c   window_close.c          \
window_discard_inputs.c   window_draw_arc.c         window_draw_arrow.c     \
window_draw_ellipse.c     window_draw_line.c        window_draw_polygon.c   \
window_draw_string.c      window_draw_triangle.c    window_fill_arc.c       \
window_fill_ellipse.c     window_fill_polygon.c     window_fill_triangle.c  \
window_get_image.c        window_get_input.c        window_get_pixel.c      \
window_get_size.c         window_get_subimage.c     window_invert_image.c   \
window_invert_subimage.c  window_load_pnmfile.c     window_load_pnmfp.c     \
window_open.c             window_put_image.c        window_put_pixel.c      \
window_put_subimage.c     window_query_pointer.c    window_rename.c         \
window_update_image.c     window_update_subimage.c  window_write_pnmfile.c  \
window_write_pnmfp.c      window_get_pointer.c
#------------------------------------------------------------------------
DIRS	= $(COREDIR) $(PALTDIR)
SRCS	= $(CORESRC) $(PALTSRC)
HEADERS	= $(COREDIR)/pixmap.h $(PALTDIR)/palette.h
#------------------------------------------------------------------------
# auto-config.
include ./config.mk
#........................................................................
VERSION	= 1.1.1
LIB_A	= lib$(LIBNAME).a
LIB_S	= lib$(LIBNAME).so.1.1.1
SONAME	= lib$(LIBNAME).so.1
LD_MAP	= lib$(LIBNAME).map
#
LIBPATH	= $(PREFIX)/$(LIBDIR)
INCPATH	= $(PREFIX)/$(INCDIR)/lib$(LIBNAME)
#........................................................................
TARGET	= $(LIB_A)

#PFLAGS	+= -DUSE_MASK_ARRAY
CFLAGS	+= -I. -I./$(INCDIR)

ifeq ($(BUILD),product)
PFLAGS	+= -DNDEBUG
else
ifeq ($(BUILD),debug)
PFLAGS	+= -DDEBUG
endif
endif

FONTSET	= 0
FONTWID	= 8
FONTHGT	= 8

ifeq ($(FONT),lpd)
FONTSET	= 1
FONTWID	= 9
FONTHGT	= 12
endif

PFLAGS	+= -DFONT_SET=$(FONTSET)

ifeq ($(GZIP),yes)
PFLAGS	+= -DUSE_PIPED_GZIP
endif

ifeq ($(PNM2B),yes)
PFLAGS	+= -DSUPPORT_MULTIBYTE_PNM
endif

ifeq ($(POLYGON),outlined)
PFLAGS	+= -DDRAW_OUTLINE
endif

ifneq ($(SHARED),no)
MAJOR	= $(shell echo $(SHARED) | awk 'BEGIN{FS="."}; {print $$1}')
MINOR	= $(shell echo $(SHARED) | awk 'BEGIN{FS="."}; {print $$2}')
ifneq ($(MAJOR),)
ifneq ($(MINOR),)
VERSION	= $(SHARED)
SONAME	= lib$(LIBNAME).so.$(MAJOR)
ifneq ($(shell ls $(WINDIR)/window_be_$(WINSYS).c 2> /dev/null),)
LIB_S	= lib$(LIBNAME)_$(WINSYS).so.$(VERSION)
else
LIB_S	= lib$(LIBNAME).so.$(VERSION)
endif
endif
endif
TARGET	+= $(LIB_S)
endif

ifneq ($(shell ls $(WINDIR)/window_be_$(WINSYS).c 2> /dev/null),)
DIRS	+= $(WINDIR)
SRCS	+= $(WINSRC) window_be_$(WINSYS).c
HEADERS	+= $(WINDIR)/window.h
#PFLAGS	+= -DPROCEED_CLIENT_MESSAGE
ifeq  ($(WINSYS),x11)
CFLAGS	+= -I$(X11DIR)/$(INCDIR)
LIBS	+= -L$(X11DIR)/$(LIBDIR) -lX11
endif
ifeq  ($(WINSYS),xlib)
CFLAGS	+= -I$(X11DIR)/$(INCDIR)
LIBS	+= -L$(X11DIR)/$(LIBDIR) -lX11
endif
ifeq  ($(MOTION),yes)
PFLAGS	+= -DDETECT_POINTER_MOTION_NOTIFY
endif
ifeq  ($(THREAD),yes)
PFLAGS	+= -DUSE_THREADED_UPDATE
LIBS	+= -lpthread
endif
endif

LIBS	+= -lm
#........................................................................
OBJS	= $(strip $(subst .c,.o,$(SRCS)))
#........................................................................
VPATH	= $(DIRS)
#------------------------------------------------------------------------
default:  $(TARGET)
	@ls -l $^

$(LIB_A): $(OBJS)
	$(AR) $@ $^
ifneq  ($(RANLIB),)
	$(RANLIB) $@
endif

$(LIB_S): $(OBJS)   $(LD_MAP)
	$(CC) -shared -o $@ -Wl,-soname,$(SONAME) -Wl,--version-script,$(LD_MAP) $(OBJS) $(LIBS)
#........................................................................
install:  $(TARGET) $(HEADERS)
	mkdir -p   $(LIBPATH) $(INCPATH)
	$(INSTALL) $(M644) $(HEADERS) $(INCPATH)
	$(INSTALL) $(M644) $(LIB_A)   $(LIBPATH)
ifneq  ($(SHARED),no)
	$(INSTALL) $(M755) $(LIB_S)   $(LIBPATH)
	cd $(LIBPATH); rm -f $(SONAME)       ; ln -s $(LIB_S) $(SONAME)
	cd $(LIBPATH); rm -f lib$(LIBNAME).so; ln -s $(LIB_S) lib$(LIBNAME).so
endif
	$(GMAKE) -C man $@

uninstall:
	rm -f  $(LIBPATH)/lib$(LIBNAME)*
	rm -rf $(INCPATH)
	$(GMAKE) -C man $@

clean:
	rm -f $(TARGET) $(LD_MAP) *.o *.h *~ core*
	for dir in $(DIRS); do \
	   for file in $${dir}/*.[ch]; do  \
	      if [ -e $${file}.tpl ]; then \
	         rm -f $${file}; \
	      fi; \
	   done;  \
	done
clobber: clean uninstall
#........................................................................
# auto-generation
$(COREDIR)/pixmap.h: pixmap.h.tpl
	sed -e "s/__PIXEL_SZ__/$(PIXELSZ)/g" \
	    -e "s/__FONT_WID__/$(FONTWID)/g" \
	    -e "s/__FONT_HGT__/$(FONTHGT)/g" < $< > $@
named_colors.h:  $(RGBTXT)
	tools/named_colors.pl  < $< > $@
palette_ids.h:   palette.h
	tools/palette_ids.pl   < $< > $@
palette_names.h: palette.h
	tools/palette_names.pl < $< > $@
$(COREDIR)/pixmap_load_pnmfile.c:  pixmap_load_pnmfile.c.tpl
	sed -e "s|__ZCAT__|`which zcat 2> /dev/null`|g"    < $< > $@
$(COREDIR)/pixmap_write_pnmfile.c: pixmap_write_pnmfile.c.tpl
	sed -e "s|__GZIP__|`which gzip 2> /dev/null`|g"    < $< > $@
$(LD_MAP): linker_map.tpl
	sed -e "s/__LIBNAME__/lib$(LIBNAME)_v$(VERSION)/g" < $< > $@
#........................................................................
# dependencies
$(OBJS): ../make.inc config.mk
#........................................................................
# pixmap module (core module)
$(subst .c,.o,$(CORESRC)): pixmap.h pixmap_internal.h
pixel_set_named_color.o:   named_colors.h
pixmap_draw_string.o:      font.h font_banner.h font_lpd.h
pixmap_load_pnmfile.o:     pixmap_load_pnmfile.c
pixmap_write_pnmfile.o:    pixmap_write_pnmfile.c
#........................................................................
# colormap module
$(subst .c,.o,$(PALTSRC)): pixmap.h palette.h palette_internal.h
palette.o:                 ds9_colors.h idl_colors.h
palette_search_id.o:       palette_ids.h
palette_search_name.o:     palette_names.h
#........................................................................
# window module
$(subst .c,.o,$(WINSRC)):  pixmap.h window.h window_be.h window_internal.h
window_be_$(WINSYS).o:     pixmap.h window.h window_be.h

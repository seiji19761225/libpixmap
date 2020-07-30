#=======================================================================
# makefile
# $Id: Makefile,v 1.1.1.11 2020/07/29 00:00:00 seiji Exp seiji $
#=======================================================================
include ../make.inc

.PHONY: default clean clobber install install_src uninstall

PFLAGS	=
LIBS	=
#-----------------------------------------------------------------------
# modules
#.......................................................................
# pixmap module (core module)
CORESRC	= libpixmap_core.f
#.......................................................................
# palette module
PALTSRC	= libpixmap_palette.f
#.......................................................................
# window module
WINSRC	= libpixmap_window.f
#-----------------------------------------------------------------------
SRCS	= $(CORESRC) $(PALTSRC)
#-----------------------------------------------------------------------
# auto-config.
include ./config.mk
#......................................................................
# FORTRAN binding library installation path
FPREFIX	= $(PREFIX)
FLIBDIR	= $(LIBDIR)
FSRCDIR	= $(SRCDIR)
FINCDIR	= $(INCDIR)
#
LIBPATH	= $(FPREFIX)/$(FLIBDIR)
SRCPATH	= $(FPREFIX)/$(FSRCDIR)/lib$(LIBNAME)/fortran
INCPATH	= $(FPREFIX)/$(FINCDIR)/lib$(LIBNAME)/fortran
#......................................................................
# core library path
CPREFIX	= ../corelib
#......................................................................
#LIBS	+= -L$(PREFIX)/$(LIBDIR) -l$(LIBNAME)
LIB_A	= lib$(LIBNAME)_fortran.a
LIB_S	= lib$(LIBNAME)_fortran.so.1.1.1
SONAME	= lib$(LIBNAME)_fortran.so.1
#......................................................................
TARGET	= $(LIB_A)

FONTW	= 8
FONTH	= 8

ifeq ($(FONT),lpd)
FONTW	= 9
FONTH	= 12
endif

PFLAGS	+= -D_PIXELSZ_=$(PIXELSZ) -D_FONTW_=$(FONTW) -D_FONTH_=$(FONTH) -DNL=32

ifneq ($(SHARED),no)
MAJOR	= $(shell echo $(SHARED) | awk 'BEGIN{FS="."}; {print $$1}')
MINOR	= $(shell echo $(SHARED) | awk 'BEGIN{FS="."}; {print $$2}')
ifneq ($(MAJOR),)
ifneq ($(MINOR),)
SONAME	= lib$(LIBNAME)_fortran.so.$(MAJOR)
LIB_S	= lib$(LIBNAME)_fortran.so.$(SHARED)
endif
endif
TARGET	+= $(LIB_S)
endif

ifneq ($(WINSYS),)
ifneq ($(WINSYS),none)
SRCS	+= $(WINSRC)
endif
endif
#.......................................................................
OBJS	= $(strip $(subst .f,.o  ,$(SRCS)))
MODS	= $(strip $(subst .f,.mod,$(SRCS)))
#-----------------------------------------------------------------------
default: $(TARGET)
	@ls -l $^
	@ls -l $(MODS)

$(LIB_A): $(SRCS) $(OBJS)
	$(AR) $@ $(OBJS)
ifneq  ($(RANLIB),)
	$(RANLIB) $@
endif

$(LIB_S): $(LIB_A)
	$(FC) -shared -o $@ -Wl,-soname,$(SONAME) $(OBJS) $(LIBS)

$(SRCS):
	$(CPP) $(PFLAGS) < $< | sed -e '/^ *$$/d' > $@
#.......................................................................
install: $(TARGET) $(MODS)
	mkdir -p   $(LIBPATH) $(INCPATH)
	$(INSTALL) $(M644) $(MODS)  $(INCPATH)
	$(INSTALL) $(M644) $(LIB_A) $(LIBPATH)
ifneq  ($(SHARED),no)
	$(INSTALL) $(M755) $(LIB_S) $(LIBPATH)
	cd $(LIBPATH); rm -f $(SONAME)               ; ln -s $(LIB_S) $(SONAME)
	cd $(LIBPATH); rm -f lib$(LIBNAME)_fortran.so; ln -s $(LIB_S) lib$(LIBNAME)_fortran.so
endif
	$(GMAKE) -C man $@

install_src: $(SRCS)
	mkdir -p   $(SRCPATH)
	$(INSTALL) $(M644) $(SRCS) $(SRCPATH)
	$(GMAKE) -C man install

uninstall:
	rm -f $(LIBPATH)/lib$(LIBNAME)_fortran*
	rm -f $(INCPATH)/libpixmap*.mod
	rm -f $(SRCPATH)/libpixmap*.f
	$(GMAKE) -C man $@

clean:
	rm -f $(TARGET) *.o *.h *.mod *~ core*
	for file in *; do \
	   if [ -e $${file}.tpl ]; then \
	       rm -f $${file}; \
	   fi; \
	done
clobber: clean uninstall
#.......................................................................
# auto-generation of header files
arrow_heads.h:   $(CPREFIX)/$(INCDIR)/lib$(LIBNAME)/pixmap.h
	tools/arrow_heads.pl   < $< > $@
palette_ids.h:   $(CPREFIX)/$(INCDIR)/lib$(LIBNAME)/palette.h
	tools/palette_ids.pl   < $< > $@
window_consts.h: $(CPREFIX)/$(INCDIR)/lib$(LIBNAME)/window.h
	tools/window_consts.pl < $< > $@
#.......................................................................
# dependencies
$(OBJS): ./config.mk ../make.inc
libpixmap_palette.o  libpixmap_window.o:     libpixmap_core.o
libpixmap_core.f:    libpixmap_core.f.tpl    arrow_heads.h
libpixmap_palette.f: libpixmap_palette.f.tpl palette_ids.h
libpixmap_window.f:  libpixmap_window.f.tpl  window_consts.h

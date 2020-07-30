#=======================================================================
# makefile
# $Id: Makefile,v 1.1.1.5 2020/07/29 00:00:00 seiji Exp seiji $
#=======================================================================
include ../make.inc

.PHONY: default clean clobber install install_src uninstall

BINS	= lines
WD_BINS	= diamond  pillar
#-----------------------------------------------------------------------
# auto-config.
CONFIG	= ../src/config.mk
PREFIX	= $(shell grep ^PREFIX  $(CONFIG) | tail -1 | awk '{printf $$3;}')
LIBNAME	= $(shell grep ^LIBNAME $(CONFIG) | tail -1 | awk '{printf $$3;}')
THREAD	= $(shell grep ^THREAD  $(CONFIG) | tail -1 | awk '{printf $$3;}')
WINSYS	= $(shell grep ^WINSYS  $(CONFIG) | tail -1 | awk '{printf $$3;}')
#
FILES	= $(shell find . -type f | grep -v -e Makefile -e RCS | sort)
SRCPATH	= $(PREFIX)/$(SRCDIR)/lib$(LIBNAME)/fortran/example
#......................................................................
PFLAGS	=
CPREFIX	= ../corelib
FPREFIX	= ../src
FFLAGS	+= -I$(FPREFIX)/$(INCDIR)/lib$(LIBNAME)
LIBS	+= -L$(FPREFIX)/$(LIBDIR) -l$(LIBNAME)_fortran -L$(CPREFIX)/$(LIBDIR) -l$(LIBNAME)
#......................................................................
ifneq ($(shell ls $(CPREFIX)/window/window_be_$(WINSYS).c 2> /dev/null),)
BINS	+= $(WD_BINS)
ifeq  ($(WINSYS),x11)
LIBS	+= -L$(X11DIR)/$(LIBDIR) -lX11
endif
ifeq  ($(WINSYS),xlib)
LIBS	+= -L$(X11DIR)/$(LIBDIR) -lX11
endif
ifeq  ($(THREAD),yes)
LIBS	+= -lpthread
endif
endif

LIBS	+= -lm
#-----------------------------------------------------------------------
default: $(BINS)
	@ls -l $^

$(BINS):
	$(FC) $(FFLAGS) $(PFLAGS) -o $@ $^ $(LIBS)

install install_src:
	mkdir -p  $(SRCPATH)
	tar -cf - $(FILES) | tar -C $(SRCPATH) -xf -

uninstall:
	rm -rf $(SRCPATH)

clean clobber:
	rm -f $(BINS) *.o *.mod *~ core*
	rm -f *.p[bgp]m *.gz
#-----------------------------------------------------------------------
# dependencies
diamond: diamond.f
lines:   lines.f
pillar:  pillar.f

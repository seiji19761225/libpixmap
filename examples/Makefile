#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# makefile
# $Id: Makefile,v 1.1.1.10 2020/07/29 00:00:00 seiji Exp seiji $
#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
include ../make.inc

.PHONY: default clean clobber install uninstall

BINS	= colorbar  cplot       mandelbrot
WD_BINS	= clock     gray-scott  pnmview     raynolds  roche  solar  star
#-----------------------------------------------------------------------
#defaults
CONFIG	= ../src/config.mk
PREFIX	= $(shell grep ^PREFIX  $(CONFIG) | tail -1 | awk '{printf $$3;}')
LIBNAME	= $(shell grep ^LIBNAME $(CONFIG) | tail -1 | awk '{printf $$3;}')
THREAD	= $(shell grep ^THREAD  $(CONFIG) | tail -1 | awk '{printf $$3;}')
WINSYS	= $(shell grep ^WINSYS  $(CONFIG) | tail -1 | awk '{printf $$3;}')
#
FILES	= $(shell find . -type f | grep -v -e Makefile -e RCS | sort)
SRCPATH	= $(PREFIX)/$(SRCDIR)/lib$(LIBNAME)/example
#.......................................................................
CPREFIX	= ../src
CFLAGS	+= -I$(CPREFIX)/$(INCDIR)
LIBS	+= -L$(CPREFIX)/$(LIBDIR) -l$(LIBNAME)
#.......................................................................
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
	$(GMAKE) -C c-ray
	@ls -l $^

$(BINS):
	$(CC) $(CFLAGS) $(PFLAGS) -o $@ $^ $(LIBS)

install:
	mkdir -p  $(SRCPATH)
	tar -cf - $(FILES) | tar -C $(SRCPATH) -xf -

uninstall:
	rm -rf $(SRCPATH)

clean clobber:
	$(GMAKE) -C c-ray $@
	rm -f $(strip $(BINS)) *.o *~ core*
	rm -f *.p[bgp]m *.gz
#-----------------------------------------------------------------------
# dependencies
clock:      clock.c
colorbar:   colorbar.c
cplot:      cplot.c
gray-scott: gray-scott.c
mandelbrot: mandelbrot.c
pnmview:    pnmview.c
raynolds:   raynolds.c
roche:      roche.c
solar:      solar.c
star:       star.c

#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# Makefile
# $Id: Makefile,v 1.1.1.6 2020/07/29 00:00:00 seiji Exp seiji $
#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
include ../../make.inc

.PHONY:	default clean clobber
#-----------------------------------------------------------------------
SRC	= c-ray.c
BIN	= c-ray
#-----------------------------------------------------------------------
# defaults
CONFIG	= ../../src/config.mk
PREFIX	= $(shell grep ^PREFIX  $(CONFIG) | tail -1 | awk '{printf $$3;}')
LIBNAME	= $(shell grep ^LIBNAME $(CONFIG) | tail -1 | awk '{printf $$3;}')
#.......................................................................
CPREFIX	= ../../src
CFLAGS	+= -I$(CPREFIX)/$(INCDIR)
LIBS	+= -L$(CPREFIX)/$(LIBDIR) -l$(LIBNAME) -lm
#-----------------------------------------------------------------------
default: $(BIN)
	@ls -l $^

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean clobber:
	rm -f $(BIN) core.* *.o *~
	rm -f *.p[bgp]m *.gz

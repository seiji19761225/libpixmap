#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# makefile
# $Id: Makefile,v 1.1.1.5 2020/07/29 00:00:00 seiji Exp seiji $
#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
include make.inc

.PHONY:
.PHONY: clean clobber default examples install src uninstall
#------------------------------------------------------------------------
default:  src
examples: src
all:      examples

src examples:
	$(GMAKE) -C $@

install uninstall:
	$(GMAKE) -C src $@
	$(GMAKE) -C examples $@

clean clobber:
	rm -f *.tgz
	$(GMAKE) -C src $@
	$(GMAKE) -C examples $@
#------------------------------------------------------------------------
-include addon.mk

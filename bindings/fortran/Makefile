#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# makefile
# $Id: Makefile,v 1.1.1.4 2020/07/29 00:00:00 seiji Exp seiji $
#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
include make.inc

.PHONY:
.PHONY: all clean clobber corelib default examples install install_src src uninstall
#------------------------------------------------------------------------
default:     src
examples:    src
all:         examples
install:     corelib
install_src: corelib
src:         corelib

src examples corelib:
	$(GMAKE) -C $@

clean clobber install install_src uninstall:
	$(GMAKE) -C src $@
	$(GMAKE) -C examples $@

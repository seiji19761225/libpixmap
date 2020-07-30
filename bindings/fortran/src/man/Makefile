#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# makefile
# $Id: Makefile,v 1.1.1.2 2016/01/20 00:00:00 seiji Exp seiji $
#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
include ../../make.inc

.PHONY: default clean clobber install uninstall
#-----------------------------------------------------------------------
MANS	= libpixmap_fortran.l
#-----------------------------------------------------------------------
#defaults
PREFIX	= $(shell grep ^PREFIX ../config.mk | tail -1 | awk '{printf $$3;}')
#.......................................................................
# FORTRAN binding library installation path
FPREFIX	= $(PREFIX)
FMANDIR	= $(MANDIR)
#-----------------------------------------------------------------------
default:

install:
	mkdir -p $(FPREFIX)/$(FMANDIR)/manl
	$(INSTALL) $(M644) $(MANS) $(FPREFIX)/$(FMANDIR)/manl

uninstall:
	if [ -d $(FPREFIX)/$(FMANDIR)/manl ]; then cd $(FPREFIX)/$(FMANDIR)/manl; rm -f $(strip $(MANS)); fi

update_db:
	if [ -x "`which mandb      2> /dev/null`" ]; then mandb      -q   $(FPREFIX)/$(FMANDIR); fi
	if [ -x "`which makewhatis 2> /dev/null`" ]; then makewhatis -s l $(FPREFIX)/$(FMANDIR); fi

clean clobber: uninstall

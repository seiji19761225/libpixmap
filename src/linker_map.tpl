#=======================================================================
# linker_map.tpl: version script for GNU ld
# (c)2015-2016 Seiji Nishimura
# $Id: linker_map.tpl,v 1.1.1.2 2016/01/13 00:00:00 seiji Exp seiji $
#=======================================================================

__LIBNAME__ {
    global:
        pixel_* ;
        palette*;
        pixmap_*;
        window_*;
    local:     *;
};

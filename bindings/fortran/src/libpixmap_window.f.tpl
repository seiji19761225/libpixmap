!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! libpixmap_window.f: FORTRAN binding of libpixmap window module
! (c)2013-2015 Seiji Nishimura
! $Id: libpixmap_window.f.tpl,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
      MODULE libpixmap_window
      USE iso_c_binding
      USE libpixmap_core
!     IMPLICIT NONE
      PUBLIC
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! constants
! device ID  ("WD_" stands for Window system Device ID. )
! key   code ("WK_" stands for Window system Key   code.)
! mouse code ("WM_" stands for Window system Mouse code.)
      INTEGER(C_INT),PARAMETER::                                        &
#include "window_consts.h"
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! data types
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_t
      TYPE,BIND(C)::window
      TYPE(pixmap)::pixmap
      TYPE(C_PTR)::be
      END TYPE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! C API interfaces
      INTERFACE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_clear_image
      SUBROUTINE window_clear_image(wd,px)                       BIND(C)
      IMPORT::window,pixel
      TYPE(window),INTENT(IN)::wd
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_clear_subimage
      SUBROUTINE window_clear_subimage(wd,px,x,y,w,h)            BIND(C)
      IMPORT::C_INT,window,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::x,y,w,h
      TYPE(window),INTENT(IN)::wd
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_close
      SUBROUTINE window_close(wd)                                BIND(C)
      IMPORT::window
      TYPE(window),INTENT(INOUT)::wd
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_discard_inputs
      SUBROUTINE window_discard_inputs(wd)                       BIND(C)
      IMPORT::window
      TYPE(window),INTENT(IN)::wd
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_draw_arc
      SUBROUTINE window_draw_arc(wd,px,xc,yc,rx,ry,theta,phi)    BIND(C)
      IMPORT::C_INT,C_DOUBLE,window,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::xc,yc,rx,ry
      REAL(C_DOUBLE),VALUE,INTENT(IN)::theta,phi
      TYPE(window),INTENT(IN)::wd
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_draw_arrow
      SUBROUTINE window_draw_arrow(wd,px,d,s,t,w,l,xs,ys,xe,ye)  BIND(C)
      IMPORT::C_BOOL,C_INT,window,pixel
      LOGICAL(C_BOOL),VALUE,INTENT(IN)::d,s
      INTEGER(C_INT),VALUE,INTENT(IN)::t,w,l,xs,ys,xe,ye
      TYPE(window),INTENT(IN)::wd
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_draw_ellipse
      SUBROUTINE window_draw_ellipse(wd,px,xc,yc,rx,ry)          BIND(C)
      IMPORT::C_INT,window,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::xc,yc,rx,ry
      TYPE(window),INTENT(IN)::wd
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_draw_line
      SUBROUTINE window_draw_line(wd,px,xs,ys,xe,ye)             BIND(C)
      IMPORT::C_INT,window,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::xs,ys,xe,ye
      TYPE(window),INTENT(IN)::wd
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_draw_polygon
      SUBROUTINE window_draw_polygon(wd,px,n,x,y)                BIND(C)
      IMPORT::C_INT,window,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::n
      INTEGER(C_INT),INTENT(IN)::x(*),y(*)
      TYPE(window),INTENT(IN)::wd
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_fill_arc
      SUBROUTINE window_fill_arc(wd,px,flg,xc,yc,rx,ry,theta,phi)       &
     &                                                           BIND(C)
      IMPORT::C_BOOL,C_INT,C_DOUBLE,window,pixel
      LOGICAL(C_BOOL),VALUE,INTENT(IN)::flg
      INTEGER(C_INT),VALUE,INTENT(IN)::xc,yc,rx,ry
      REAL(C_DOUBLE),VALUE,INTENT(IN)::theta,phi
      TYPE(window),INTENT(IN)::wd
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_fill_ellipse
      SUBROUTINE window_fill_ellipse(wd,px,xc,yc,rx,ry)          BIND(C)
      IMPORT::C_INT,window,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::xc,yc,rx,ry
      TYPE(window),INTENT(IN)::wd
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_fill_polygon
      SUBROUTINE window_fill_polygon(wd,px,n,x,y)                BIND(C)
      IMPORT::C_INT,window,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::n
      INTEGER(C_INT),INTENT(IN)::x(*),y(*)
      TYPE(window),INTENT(IN)::wd
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_fill_triangle
      SUBROUTINE window_fill_triangle(wd,px,x0,y0,x1,y1,x2,y2)   BIND(C)
      IMPORT::C_INT,window,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::x0,y0,x1,y1,x2,y2
      TYPE(window),INTENT(IN)::wd
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_get_image
      SUBROUTINE window_get_image(wd,pm)                         BIND(C)
      IMPORT::window,pixmap
      TYPE(window),INTENT(IN)::wd
      TYPE(pixmap),INTENT(OUT)::pm
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_get_input
      SUBROUTINE window_get_input(wd,sync,device,code,x,y)       BIND(C)
      IMPORT::C_INT,C_BOOL,window
      INTEGER(C_INT),INTENT(OUT)::device,code,x,y
      LOGICAL(C_BOOL),VALUE,INTENT(IN)::sync
      TYPE(window),INTENT(IN)::wd
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_get_pixel
      PURE SUBROUTINE window_get_pixel(wd,px,x,y)                BIND(C)
      IMPORT::C_INT,window,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::x,y
      TYPE(window),INTENT(IN)::wd
      TYPE(pixel),INTENT(OUT)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_get_size
      PURE SUBROUTINE window_get_size(wd,w,h)                    BIND(C)
      IMPORT::C_INT,window
      INTEGER(C_INT),INTENT(OUT)::w,h
      TYPE(window),INTENT(IN)::wd
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_get_subimage
      SUBROUTINE window_get_subimage(wd,x,y,pm,w,h)              BIND(C)
      IMPORT::C_INT,window,pixmap
      INTEGER(C_INT),VALUE,INTENT(IN)::x,y,w,h
      TYPE(window),INTENT(IN)::wd
      TYPE(pixmap),INTENT(OUT)::pm
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_invert_image
      SUBROUTINE window_invert_image(wd)                         BIND(C)
      IMPORT::window
      TYPE(window),INTENT(IN)::wd
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_invert_subimage
      SUBROUTINE window_invert_subimage(wd,x,y,w,h)              BIND(C)
      IMPORT::C_INT,window
      INTEGER(C_INT),VALUE,INTENT(IN)::x,y,w,h
      TYPE(window),INTENT(IN)::wd
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_put_image
      SUBROUTINE window_put_image(wd,pm)                         BIND(C)
      IMPORT::window,pixmap
      TYPE(window),INTENT(IN)::wd
      TYPE(pixmap),INTENT(IN)::pm
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_put_pixel
      SUBROUTINE window_put_pixel(wd,px,x,y)                     BIND(C)
      IMPORT::C_INT,window,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::x,y
      TYPE(window),INTENT(IN)::wd
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_put_subimage
      SUBROUTINE window_put_subimage(wd,wx,wy,pm,px,py,w,h)      BIND(C)
      IMPORT::C_INT,window,pixmap
      INTEGER(C_INT),VALUE,INTENT(IN)::wx,wy,px,py,w,h
      TYPE(window),INTENT(IN)::wd
      TYPE(pixmap),INTENT(IN)::pm
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_query_pointer
      SUBROUTINE window_query_pointer(wd,x,y)                    BIND(C)
      IMPORT::C_INT,window
      INTEGER(C_INT),INTENT(OUT)::x,y
      TYPE(window),INTENT(IN)::wd
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_update_image
      SUBROUTINE window_update_image(wd)                         BIND(C)
      IMPORT::window
      TYPE(window),INTENT(IN)::wd
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_update_subimage
      SUBROUTINE window_update_subimage(wd,x,y,w,h)              BIND(C)
      IMPORT::C_INT,window
      INTEGER(C_INT),VALUE,INTENT(IN)::x,y,w,h
      TYPE(window),INTENT(IN)::wd
      END SUBROUTINE
      END INTERFACE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! wrapper procedures
      CONTAINS
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_draw_string
      SUBROUTINE window_draw_string(wd,px,xs,ys,str)
      INTEGER,INTENT(IN)::xs,ys
      CHARACTER(LEN=*),INTENT(IN)::str
      TYPE(window),INTENT(IN)::wd
      TYPE(pixel),INTENT(IN)::px
      INTERFACE
      SUBROUTINE c_window_draw_string(wd,px,xs,ys,str)                  &
     &                                 BIND(C,NAME='window_draw_string')
      IMPORT::C_INT,C_CHAR,window,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::xs,ys
      CHARACTER(C_CHAR),INTENT(IN)::str(*)
      TYPE(window),INTENT(IN)::wd
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
      END INTERFACE
      CALL c_window_draw_string(wd,px,xs,ys,TRIM(str)//C_NULL_CHAR)
      RETURN
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_load_pnmfile
      SUBROUTINE window_load_pnmfile(wd,fname,istat)
      USE iso_fortran_env,ONLY:ERROR_UNIT
      CHARACTER(LEN=*),INTENT(IN)::fname
      INTEGER,OPTIONAL,INTENT(OUT)::istat
      TYPE(window),INTENT(OUT)::wd
      INTEGER::ierr
      INTERFACE
      FUNCTION c_window_load_pnmfile(wd,fname)                          &
     &                                BIND(C,NAME='window_load_pnmfile')
      IMPORT::C_INT,C_CHAR,window
      INTEGER(C_INT)::c_window_load_pnmfile
      CHARACTER(C_CHAR),INTENT(IN)::fname(*)
      TYPE(window),INTENT(OUT)::wd
      END FUNCTION
      END INTERFACE
      ierr=c_window_load_pnmfile(wd,TRIM(fname)//C_NULL_CHAR)
      IF (PRESENT(istat)) THEN
         istat=ierr
      ELSE IF (ierr/=0) THEN
         WRITE(ERROR_UNIT,100) 'window_load_pnmfile',TRIM(fname)
      END IF
      RETURN
 100  FORMAT('I/O error happened in ',A,' call for ',A,'.')
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_open
      SUBROUTINE window_open(wd,w,h,wname)
      INTEGER,INTENT(IN)::w,h
      CHARACTER(LEN=*),INTENT(IN)::wname
      TYPE(window),INTENT(OUT)::wd
      INTERFACE
      SUBROUTINE c_window_open(wd,w,h,wname)  BIND(C,NAME='window_open')
      IMPORT::C_INT,C_CHAR,window
      INTEGER(C_INT),VALUE,INTENT(IN)::w,h
      CHARACTER(C_CHAR),INTENT(IN)::wname(*)
      TYPE(window),INTENT(OUT)::wd
      END SUBROUTINE
      END INTERFACE
      CALL c_window_open(wd,w,h,TRIM(wname)//C_NULL_CHAR)
      RETURN
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_rename
      SUBROUTINE window_rename(wd,wname)
      CHARACTER(LEN=*),INTENT(IN)::wname
      TYPE(window),INTENT(OUT)::wd
      INTERFACE
      SUBROUTINE c_window_rename(wd,wname)  BIND(C,NAME='window_rename')
      IMPORT::C_CHAR,window
      CHARACTER(C_CHAR),INTENT(IN)::wname(*)
      TYPE(window),INTENT(OUT)::wd
      END SUBROUTINE
      END INTERFACE
      CALL c_window_rename(wd,TRIM(wname)//C_NULL_CHAR)
      RETURN
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! window_write_pnmfile
      SUBROUTINE window_write_pnmfile(wd,fname,istat)
      USE iso_fortran_env,ONLY:ERROR_UNIT
      CHARACTER(LEN=*),INTENT(IN)::fname
      INTEGER,OPTIONAL,INTENT(OUT)::istat
      TYPE(window),INTENT(IN)::wd
      INTEGER::ierr
      INTERFACE
      FUNCTION c_window_write_pnmfile(wd,fname)                         &
     &                               BIND(C,NAME='window_write_pnmfile')
      IMPORT::C_INT,C_CHAR,window
      INTEGER(C_INT)::c_window_write_pnmfile
      CHARACTER(C_CHAR),INTENT(IN)::fname(*)
      TYPE(window),INTENT(IN)::wd
      END FUNCTION
      END INTERFACE
      ierr=c_window_write_pnmfile(wd,TRIM(fname)//C_NULL_CHAR)
      IF (PRESENT(istat)) THEN
         istat=ierr
      ELSE IF (ierr/=0) THEN
         WRITE(ERROR_UNIT,100) 'window_write_pnmfile',TRIM(fname)
      END IF
      RETURN
 100  FORMAT('I/O error happened in ',A,' call for ',A,'.')
      END SUBROUTINE
      END MODULE

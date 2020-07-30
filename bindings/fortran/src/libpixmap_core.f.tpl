!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! libpixmap_core.f: FORTRAN binding of libpixmap core module (=pixmap module)
! (c)2013-2015 Seiji Nishimura
! $Id: libpixmap_core.f.tpl,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
      MODULE libpixmap_core
      USE iso_c_binding
!     IMPLICIT NONE
      PUBLIC
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! constants
      LOGICAL(C_BOOL),PARAMETER::TRUE=.TRUE.,FALSE=.FALSE.
      INTEGER,PARAMETER::                                               &
     &   SIZEOF_PIXEL=_PIXELSZ_,FONT_WIDTH=_FONTW_,FONT_HEIGHT=_FONTH_
! for pixmap_draw_arrow
      INTEGER(C_INT),PARAMETER::                                        &
#include "arrow_heads.h"
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! data types
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixel_t
      TYPE,BIND(C)::pixel
#if _PIXELSZ_ == 4
      INTEGER(C_INT8_T)::pad
#endif
      INTEGER(C_INT8_T)::r,g,b
      END TYPE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_t
      TYPE,BIND(C)::pixmap
      INTEGER(C_INT)::width,height
      TYPE(C_PTR)::data
      END TYPE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! C API interfaces
      INTERFACE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixel_blend
      PURE FUNCTION pixel_blend(alpha,p,q)                       BIND(C)
      IMPORT::C_DOUBLE,pixel
      TYPE(pixel)::pixel_blend
      REAL(C_DOUBLE),VALUE,INTENT(IN)::alpha
      TYPE(pixel),VALUE,INTENT(IN)::p,q
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixel_invert
      PURE FUNCTION pixel_invert(p)                              BIND(C)
      IMPORT::pixel
      TYPE(pixel)::pixel_invert
      TYPE(pixel),VALUE,INTENT(IN)::p
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_blend_image
      SUBROUTINE pixmap_blend_image(alpha,p1,p2)                 BIND(C)
      IMPORT::C_DOUBLE,pixmap
      REAL(C_DOUBLE),VALUE,INTENT(IN)::alpha
      TYPE(pixmap),INTENT(IN)::p1,p2
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_blend_subimage
      SUBROUTINE pixmap_blend_subimage(alpha,p1,x1,y1,p2,x2,y2,w,h)     &
     &                                                           BIND(C)
      IMPORT::C_DOUBLE,C_INT,pixmap
      REAL(C_DOUBLE),VALUE,INTENT(IN)::alpha
      INTEGER(C_INT),VALUE,INTENT(IN)::x1,y1,x2,y2,w,h
      TYPE(pixmap),INTENT(IN)::p1,p2
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_clear_image
      SUBROUTINE pixmap_clear_image(pm,px)                       BIND(C)
      IMPORT::pixmap,pixel
      TYPE(pixmap),INTENT(IN)::pm
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_clear_subimage
      SUBROUTINE pixmap_clear_subimage(pm,px,x,y,w,h)            BIND(C)
      IMPORT::C_INT,pixmap,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::x,y,w,h
      TYPE(pixmap),INTENT(IN)::pm
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_copy_image
      SUBROUTINE pixmap_copy_image(p1,p2)                        BIND(C)
      IMPORT::pixmap
      TYPE(pixmap),INTENT(IN)::p1,p2
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_copy_subimage
      SUBROUTINE pixmap_copy_subimage(p1,x1,y1,p2,x2,y2,w,h)     BIND(C)
      IMPORT::C_INT,pixmap
      INTEGER(C_INT),VALUE,INTENT(IN)::x1,y1,x2,y2,w,h
      TYPE(pixmap),INTENT(IN)::p1,p2
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_create
      SUBROUTINE pixmap_create(pm,w,h)                           BIND(C)
      IMPORT::C_INT,pixmap
      INTEGER(C_INT),VALUE,INTENT(IN)::w,h
      TYPE(pixmap),INTENT(OUT)::pm
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_destroy
      SUBROUTINE pixmap_destroy(pm)                              BIND(C)
      IMPORT::pixmap
      TYPE(pixmap),INTENT(INOUT)::pm
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_draw_arc
      SUBROUTINE pixmap_draw_arc(pm,px,xc,yc,rx,ry,theta,phi)    BIND(C)
      IMPORT::C_INT,C_DOUBLE,pixmap,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::xc,yc,rx,ry
      REAL(C_DOUBLE),VALUE,INTENT(IN)::theta,phi
      TYPE(pixmap),INTENT(IN)::pm
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_draw_arrow
      SUBROUTINE pixmap_draw_arrow(pm,px,d,s,t,w,l,xs,ys,xe,ye)  BIND(C)
      IMPORT::C_BOOL,C_INT,pixmap,pixel
      LOGICAL(C_BOOL),VALUE,INTENT(IN)::d,s
      INTEGER(C_INT),VALUE,INTENT(IN)::t,w,l,xs,ys,xe,ye
      TYPE(pixmap),INTENT(IN)::pm
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_draw_ellipse
      SUBROUTINE pixmap_draw_ellipse(pm,px,xc,yc,rx,ry)          BIND(C)
      IMPORT::C_INT,pixmap,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::xc,yc,rx,ry
      TYPE(pixmap),INTENT(IN)::pm
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_draw_line
      SUBROUTINE pixmap_draw_line(pm,px,xs,ys,xe,ye)             BIND(C)
      IMPORT::C_INT,pixmap,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::xs,ys,xe,ye
      TYPE(pixmap),INTENT(IN)::pm
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_draw_polygon
      SUBROUTINE pixmap_draw_polygon(pm,px,n,x,y)                BIND(C)
      IMPORT::C_INT,pixmap,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::n
      INTEGER(C_INT),INTENT(IN)::x(*),y(*)
      TYPE(pixmap),INTENT(IN)::pm
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_fill_arc
      SUBROUTINE pixmap_fill_arc(pm,px,flg,xc,yc,rx,ry,theta,phi)       &
     &                                                           BIND(C)
      IMPORT::C_BOOL,C_INT,C_DOUBLE,pixmap,pixel
      LOGICAL(C_BOOL),VALUE,INTENT(IN)::flg
      INTEGER(C_INT),VALUE,INTENT(IN)::xc,yc,rx,ry
      REAL(C_DOUBLE),VALUE,INTENT(IN)::theta,phi
      TYPE(pixmap),INTENT(IN)::pm
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_fill_ellipse
      SUBROUTINE pixmap_fill_ellipse(pm,px,xc,yc,rx,ry)          BIND(C)
      IMPORT::C_INT,pixmap,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::xc,yc,rx,ry
      TYPE(pixmap),INTENT(IN)::pm
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_fill_polygon
      SUBROUTINE pixmap_fill_polygon(pm,px,n,x,y)                BIND(C)
      IMPORT::C_INT,pixmap,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::n
      INTEGER(C_INT),INTENT(IN)::x(*),y(*)
      TYPE(pixmap),INTENT(IN)::pm
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_fill_triangle
      SUBROUTINE pixmap_fill_triangle(pm,px,x0,y0,x1,y1,x2,y2)   BIND(C)
      IMPORT::C_INT,pixmap,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::x0,y0,x1,y1,x2,y2
      TYPE(pixmap),INTENT(IN)::pm
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_get_pixel
      PURE SUBROUTINE pixmap_get_pixel(pm,px,x,y)                BIND(C)
      IMPORT::C_INT,pixmap,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::x,y
      TYPE(pixmap),INTENT(IN)::pm
      TYPE(pixel),INTENT(OUT)::px
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_get_size
      PURE SUBROUTINE pixmap_get_size(pm,w,h)                    BIND(C)
      IMPORT::C_INT,pixmap
      INTEGER(C_INT),INTENT(OUT)::w,h
      TYPE(pixmap),INTENT(IN)::pm
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_invert_image
      SUBROUTINE pixmap_invert_image(pm)                         BIND(C)
      IMPORT::pixmap
      TYPE(pixmap),INTENT(IN)::pm
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_invert_subimage
      SUBROUTINE pixmap_invert_subimage(pm,x,y,w,h)              BIND(C)
      IMPORT::C_INT,pixmap
      INTEGER(C_INT),VALUE,INTENT(IN)::x,y,w,h
      TYPE(pixmap),INTENT(IN)::pm
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_put_pixel
      SUBROUTINE pixmap_put_pixel(pm,px,x,y)                     BIND(C)
      IMPORT::C_INT,pixmap,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::x,y
      TYPE(pixmap),INTENT(IN)::pm
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
      END INTERFACE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! wrapper procedures
      CONTAINS
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixel_get_r
      PURE FUNCTION pixel_get_r(p)
      INTEGER pixel_get_r
      TYPE(pixel),INTENT(IN)::p
      pixel_get_r=p%r
      ! FORTRAN cannot deal with unsigned integer:
      ! assume two's complement representation.
      IF (pixel_get_r<0) pixel_get_r=pixel_get_r+256
      RETURN
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixel_get_g
      PURE FUNCTION pixel_get_g(p)
      INTEGER pixel_get_g
      TYPE(pixel),INTENT(IN)::p
      pixel_get_g=p%g
      ! FORTRAN cannot deal with unsigned integer:
      ! assume two's complement representation.
      IF (pixel_get_g<0) pixel_get_g=pixel_get_g+256
      RETURN
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixel_get_b
      PURE FUNCTION pixel_get_b(p)
      INTEGER pixel_get_b
      TYPE(pixel),INTENT(IN)::p
      pixel_get_b=p%b
      ! FORTRAN cannot deal with unsigned integer:
      ! assume two's complement representation.
      IF (pixel_get_b<0) pixel_get_b=pixel_get_b+256
      RETURN
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixel_set_rgb
      PURE FUNCTION pixel_set_rgb(r,g,b)
      TYPE(pixel)::pixel_set_rgb
      INTEGER,INTENT(IN)::r,g,b
#if _PIXELSZ_ == 4
      pixel_set_rgb%pad=0
#endif
      pixel_set_rgb%r  =r
      pixel_set_rgb%g  =g
      pixel_set_rgb%b  =b
      RETURN
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixel_set_named_color
      PURE FUNCTION pixel_set_named_color(str)
      TYPE(pixel)::pixel_set_named_color
      CHARACTER(LEN=*),INTENT(IN)::str
      INTERFACE
      PURE FUNCTION c_pixel_set_named_color(str)                        &
     &                              BIND(C,NAME='pixel_set_named_color')
      IMPORT::C_CHAR,pixel
      TYPE(pixel)::c_pixel_set_named_color
      CHARACTER(C_CHAR),INTENT(IN)::str(*)
      END FUNCTION
      END INTERFACE
      pixel_set_named_color=                                            &
     &         c_pixel_set_named_color(TRIM(str)//C_NULL_CHAR)
      RETURN
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_draw_string
      SUBROUTINE pixmap_draw_string(pm,px,xs,ys,str)
      INTEGER,INTENT(IN)::xs,ys
      CHARACTER(LEN=*),INTENT(IN)::str
      TYPE(pixmap),INTENT(IN)::pm
      TYPE(pixel),INTENT(IN)::px
      INTERFACE
      SUBROUTINE c_pixmap_draw_string(pm,px,xs,ys,str)                  &
     &                                 BIND(C,NAME='pixmap_draw_string')
      IMPORT::C_INT,C_CHAR,pixmap,pixel
      INTEGER(C_INT),VALUE,INTENT(IN)::xs,ys
      CHARACTER(C_CHAR),INTENT(IN)::str(*)
      TYPE(pixmap),INTENT(IN)::pm
      TYPE(pixel),VALUE,INTENT(IN)::px
      END SUBROUTINE
      END INTERFACE
      CALL c_pixmap_draw_string(pm,px,xs,ys,TRIM(str)//C_NULL_CHAR)
      RETURN
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_load_pnmfile
      SUBROUTINE pixmap_load_pnmfile(pm,fname,istat)
      USE iso_fortran_env,ONLY:ERROR_UNIT
      CHARACTER(LEN=*),INTENT(IN)::fname
      INTEGER,OPTIONAL,INTENT(OUT)::istat
      TYPE(pixmap),INTENT(OUT)::pm
      INTEGER::ierr
      INTERFACE
      FUNCTION c_pixmap_load_pnmfile(pm,fname)                          &
     &                                BIND(C,NAME='pixmap_load_pnmfile')
      IMPORT::C_INT,C_CHAR,pixmap
      INTEGER(C_INT)::c_pixmap_load_pnmfile
      CHARACTER(C_CHAR),INTENT(IN)::fname(*)
      TYPE(pixmap),INTENT(OUT)::pm
      END FUNCTION
      END INTERFACE
      ierr=c_pixmap_load_pnmfile(pm,TRIM(fname)//C_NULL_CHAR)
      IF (PRESENT(istat)) THEN
         istat=ierr
      ELSE IF (ierr/=0) THEN
         WRITE(ERROR_UNIT,100) 'pixmap_load_pnmfile',TRIM(fname)
      END IF
      RETURN
 100  FORMAT('I/O error happened in ',A,' call for ',A,'.')
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! pixmap_write_pnmfile
      SUBROUTINE pixmap_write_pnmfile(pm,fname,istat)
      USE iso_fortran_env,ONLY:ERROR_UNIT
      CHARACTER(LEN=*),INTENT(IN)::fname
      INTEGER,OPTIONAL,INTENT(OUT)::istat
      TYPE(pixmap),INTENT(IN)::pm
      INTEGER::ierr
      INTERFACE
      FUNCTION c_pixmap_write_pnmfile(pm,fname)                         &
     &                               BIND(C,NAME='pixmap_write_pnmfile')
      IMPORT::C_INT,C_CHAR,pixmap
      INTEGER(C_INT)::c_pixmap_write_pnmfile
      CHARACTER(C_CHAR),INTENT(IN)::fname(*)
      TYPE(pixmap),INTENT(IN)::pm
      END FUNCTION
      END INTERFACE
      ierr=c_pixmap_write_pnmfile(pm,TRIM(fname)//C_NULL_CHAR)
      IF (PRESENT(istat)) THEN
         istat=ierr
      ELSE IF (ierr/=0) THEN
         WRITE(ERROR_UNIT,100) 'pixmap_write_pnmfile',TRIM(fname)
      END IF
      RETURN
 100  FORMAT('I/O error happened in ',A,' call for ',A,'.')
      END SUBROUTINE
      END MODULE

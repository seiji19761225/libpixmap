! lines.f
! (c)2004-2009,2013-2015 Seiji Nishimura
! $Id: lines.f,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
      PROGRAM LINES
      USE libpixmap_core
      IMPLICIT REAL*8(A-H,O-Z)
      INTEGER,PARAMETER::IWIDTH=800,IHEIGHT=450,IR=200,II=20,           &
     &                   ICX=IWIDTH/2,ICY=IHEIGHT/2
      REAL(8),PARAMETER::PI=3.14159265358979323846D0
      TYPE(PIXMAP)::IMAGE
      TYPE(PIXEL)::COLOR
! inline function
      IROUND(X)=INT(X+0.5)
!
      CALL PIXMAP_CREATE(IMAGE,IWIDTH,IHEIGHT)
!
      COLOR=PIXEL_SET_RGB(INT(Z"FF"),INT(Z"FF"),INT(Z"FF"))
      CALL PIXMAP_CLEAR_IMAGE(IMAGE,COLOR)
!
      COLOR=PIXEL_SET_RGB(INT(Z"00"),INT(Z"FF"),INT(Z"FF"))
      CALL PIXMAP_DRAW_ELLIPSE(IMAGE,COLOR,ICX,ICY,IR,IR)
      CALL PIXMAP_DRAW_LINE(IMAGE,COLOR,0,ICY,IWIDTH -1,ICY)
      CALL PIXMAP_DRAW_LINE(IMAGE,COLOR,ICX,0,ICX,IHEIGHT-1)
      CALL PIXMAP_DRAW_LINE(IMAGE,COLOR,ICX+IR,ICY,ICX,ICY+IR)
      CALL PIXMAP_DRAW_LINE(IMAGE,COLOR,ICX+IR,ICY,ICX,ICY-IR)
      CALL PIXMAP_DRAW_LINE(IMAGE,COLOR,ICX-IR,ICY,ICX,ICY+IR)
      CALL PIXMAP_DRAW_LINE(IMAGE,COLOR,ICX-IR,ICY,ICX,ICY-IR)
!
      DO I=II,IR,II
         PHI=0.5*PI*I/IR
         ISN=IROUND(IR*DSIN(PHI))
         ICS=IROUND(IR*DCOS(PHI))
         CALL PIXMAP_DRAW_LINE(IMAGE,COLOR,ICX+ISN,ICY,ICX,ICY+ICS)
         CALL PIXMAP_DRAW_LINE(IMAGE,COLOR,ICX+ISN,ICY,ICX,ICY-ICS)
         CALL PIXMAP_DRAW_LINE(IMAGE,COLOR,ICX-ISN,ICY,ICX,ICY-ICS)
         CALL PIXMAP_DRAW_LINE(IMAGE,COLOR,ICX-ISN,ICY,ICX,ICY+ICS)
         CALL PIXMAP_DRAW_LINE(IMAGE,COLOR,ICX+ICS,ICY,ICX,ICY+ISN)
         CALL PIXMAP_DRAW_LINE(IMAGE,COLOR,ICX+ICS,ICY,ICX,ICY-ISN)
         CALL PIXMAP_DRAW_LINE(IMAGE,COLOR,ICX-ICS,ICY,ICX,ICY-ISN)
         CALL PIXMAP_DRAW_LINE(IMAGE,COLOR,ICX-ICS,ICY,ICX,ICY+ISN)
      END DO
!
      CALL PIXMAP_WRITE_PNMFILE(IMAGE,'output.ppm')
!
      CALL PIXMAP_DESTROY(IMAGE)
!
      STOP
      END

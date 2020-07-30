!-----------------------------------------------------------------------
! diamond.f
! (c)2004-2010,2013-2015 Seiji Nishimura
! $Id: diamond.f,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
!-----------------------------------------------------------------------
      MODULE PARAMETERS
      IMPLICIT REAL(8)(A-H,O-Z)
      REAL(8),PARAMETER::PI=3.14159265358979323846D0
      INTEGER,PARAMETER::SIZE=512,XC=SIZE/2,YC=SIZE/2,M=36
      END MODULE
!-----------------------------------------------------------------------
      PROGRAM MAIN
      USE PARAMETERS
      USE libpixmap_window
      IMPLICIT REAL(8)(A-H,O-Z)
!
      TYPE(WINDOW)::GFX
      LOGICAL,EXTERNAL::ESC_IS_PUSHED
!
      INTERFACE
         FUNCTION USLEEP(USEC) BIND(C)
            IMPORT::C_INT
            INTEGER(C_INT)::USLEEP
            INTEGER(C_INT),VALUE,INTENT(IN)::USEC
         END FUNCTION
      END INTERFACE
!
      CALL WINDOW_OPEN(GFX,SIZE,SIZE,'diamond')

      I=0

      DO WHILE (.not.ESC_IS_PUSHED(GFX))
         I=MOD(I+2,2*M)
         N=MERGE(2*M-I,I,I>M)
         IF (N==0) CYCLE
         CALL DRAW_DIAMOND(GFX,N)
         IF (USLEEP(125000)/=0) PRINT*,'USLEEP: ERROR HAPPENED.'
      END DO

      CALL WINDOW_CLOSE(GFX)
!
      STOP
      END PROGRAM
!-----------------------------------------------------------------------
      SUBROUTINE DRAW_DIAMOND(GFX,N)
      USE PARAMETERS
      USE libpixmap_core
      USE libpixmap_window
      USE libpixmap_palette
      IMPLICIT REAL(8)(A-H,O-Z)
!
      INTEGER,INTENT(IN)::N
      INTEGER::X(M),Y(M)
      TYPE(WINDOW),INTENT(IN)::GFX
      TYPE(PIXEL)::COLOR
! inline function
      IROUND(D)=INT(D+0.5D0)
!
      ARG   =PI*N/M
      RADIUS=DSIN(0.5*ARG)*SIZE/2.D0
!
      DO I=1,N
         X(I)=IROUND(RADIUS*DCOS(2.D0*PI*I/N)+XC)
         Y(I)=IROUND(RADIUS*DSIN(2.D0*PI*I/N)+YC)
      END DO
!
      COLOR=PIXEL_SET_NAMED_COLOR('black')
      CALL WINDOW_CLEAR_IMAGE(GFX,COLOR)
!
      COLOR=PALETTE(IDL2_WAVES,-1.D0,1.D0,DCOS(ARG))
      DO I=1,N
         DO J=I+1,N
            CALL WINDOW_DRAW_LINE(GFX,COLOR,X(I),Y(I),X(J),Y(J))
         END DO
      END DO
!
      CALL WINDOW_UPDATE_IMAGE(GFX)
!
      RETURN
      END SUBROUTINE
!-----------------------------------------------------------------------
      FUNCTION ESC_IS_PUSHED(GFX)
      USE libpixmap_window
      IMPLICIT REAL(8)(A-H,O-Z)
      LOGICAL::ESC_IS_PUSHED
      TYPE(WINDOW),INTENT(IN)::GFX
      INTEGER::DEVICE,CODE,X,Y
!
      ESC_IS_PUSHED=.FALSE.
 
      DEVICE=WD_KEYBOARD
      CODE  =WK_NULL
      X     =0
      Y     =0
 
      DO WHILE (DEVICE/=WD_NULL)
         CALL WINDOW_GET_INPUT(GFX,FALSE,DEVICE,CODE,X,Y)
         IF (DEVICE==WD_KEYBOARD.and.CODE==WK_ESC) THEN
            ESC_IS_PUSHED=.TRUE.
            EXIT
         END IF
      END DO
!
      RETURN
      END FUNCTION

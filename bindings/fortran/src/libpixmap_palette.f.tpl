!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! libpixmap_palette.f: FORTRAN binding of libpixmap palette module
! (c)2013-2015 Seiji Nishimura
! $Id: libpixmap_palette.f.tpl,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
      MODULE libpixmap_palette
      USE iso_c_binding
      USE libpixmap_core,ONLY:pixel
!     IMPLICIT NONE
      PUBLIC
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! constants
      INTEGER,PARAMETER::              PALETTE_NAME_MAX_LENGTH     =NL, &
#include "palette_ids.h"
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! C API interfaces
      INTERFACE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! palette
      PURE FUNCTION palette(id,dmin,dmax,dat)                   BIND(C)
      IMPORT::C_INT,C_DOUBLE,pixel
      TYPE(pixel)::palette
      INTEGER(C_INT),VALUE,INTENT(IN)::id
      REAL(C_DOUBLE),VALUE,INTENT(IN)::dmin,dmax,dat
      END FUNCTION
      END INTERFACE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! wrapper procedures
      CONTAINS
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! palette_search_id
      PURE FUNCTION palette_search_id(cname)
      INTEGER::palette_search_id
      CHARACTER(LEN=*),INTENT(IN)::cname
      INTERFACE
      PURE FUNCTION c_palette_search_id(cname)                          &
     &                                 BIND(C,NAME='palette_search_id')
      IMPORT::C_INT,C_CHAR
      INTEGER(C_INT)::c_palette_search_id
      CHARACTER(C_CHAR),INTENT(IN)::cname(*)
      END FUNCTION
      END INTERFACE
      palette_search_id=c_palette_search_id(TRIM(cname)//C_NULL_CHAR)
      RETURN
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! palette_search_name
      FUNCTION palette_search_name(id)
      CHARACTER(LEN=palette_name_max_length)::palette_search_name
      INTEGER,INTENT(IN)::id
      CHARACTER,POINTER::fp(:)
      TYPE(C_PTR)::cp
      INTERFACE
      FUNCTION c_palette_search_name(id)                                &
     &                               BIND(C,NAME='palette_search_name')
      IMPORT::C_PTR,C_INT
      TYPE(C_PTR)::c_palette_search_name
      INTEGER(C_INT),VALUE,INTENT(IN)::id
      END FUNCTION
      END INTERFACE
      palette_search_name(:)=' '
      cp=c_palette_search_name(id)
      IF (C_ASSOCIATED(cp)) THEN
          CALL C_F_POINTER(cp,fp,SHAPE=[palette_name_max_length])
          DO i=1,palette_name_max_length
             IF (fp(i)==C_NULL_CHAR) EXIT
             palette_search_name(i:i)=fp(i)
          END DO
      END IF
      RETURN
      END FUNCTION
      END MODULE

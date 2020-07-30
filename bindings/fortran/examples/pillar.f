*
* pillar.f
* (c)2004-2009,2013-2015 Seiji Nishimura
* $Id: pillar.f,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
*
*=================================================================*
*  2-Dimensional Flow around Square a Pillar by velocity          *
*       and pressure with FDM and SOR                             *
*-----------------------------------------------------------------*
*    Written by Yasunori Ushiro,   2003/09/14                     *
*        ( Hitachi Ltd. and Waseda University )                   *
*=================================================================*
      USE libpixmap_window
      IMPLICIT REAL*8(A-H,O-Z)
      PARAMETER(NDX=301, NDY=301)
      DIMENSION U(-1:NDX,-1:NDY), V(-1:NDX,-1:NDY)
      DIMENSION A(-1:NDX,-1:NDY,5), B(-1:NDX,-1:NDY)
      DIMENSION P(-1:NDX,-1:NDY), PHI(-1:NDX,-1:NDY)
      COMMON /MESH/NX,NX1,NX2,NY,NY1,NY2
      TYPE(WINDOW)::GFX_WINDOW
      COMMON/GFX/GFX_WINDOW
      INTEGER,PARAMETER::X_FACTOR=6,Y_FACTOR=3
*  Initial Data
      ID = 0
      CALL XCLOCK(T1,3)
      XM = 2.0
      YM = 1.0
      WRITE(6,*) 'Type In  NX,NY'
      READ(5,*) NX,NY
      WRITE(6,*) 'Type in  Re,DT,NT(Total NO.),MT(Output Interval)'
      READ(5,*) Re,dt,NT,MT
      if(NX.ge.NDX) NX = NDX - 1
      if(NY.ge.NDY) NY = NDY - 1
      NX1 = NX*2/10
      NX2 = NX*3/10
      NY1 = NY*2/5
      NY2 = NY*3/5
      WRITE(6,100) XM,NX1,NX2,NX
      WRITE(6,110) YM,NY1,NY2,NY
      WRITE(6,120) Re,dt,NT,MT
*  Initial Constant
      T   = 0.0
      hx  = XM/NX
      hy  = YM/NY
      dx  = 1.0/(2.0*hx)
      dy  = 1.0/(2.0*hy)
      ddx = 1.0/hx**2
      ddy = 1.0/hy**2
      EPS = 1.0e-4
      OMG = 1.0 + DLOG((NX+NY)*1.0D0)/DLOG((NDX+NDY)*1.2D0)
*   Set Initial U,V
      ITER = NX*NY
      CALL PHISOL(PHI,A,B,U,V,hx,hy,OMG,NDX,NDY,EPS,ITER)
*   Set Initial P
      do j=-1,NY+1
        do i=-1,NX+1
          P(i,j) = 0.0
        end do
      end do
*
      CALL WINDOW_OPEN(GFX_WINDOW,X_FACTOR*(NX+1),
     &                            Y_FACTOR*(NY+1),'pillar')
*
      CALL OUTUVP(P,U,V,PHI,hx,hy,NDX,NDY)
*  Main Loop
      CALL XCLOCK(T1,5)
      NITER = ITER
      do k=1,NT
        T = T + DT
*   Compute P
        ITER = NX*NY
        CALL PSOL(P,A,B,U,V,hx,hy,dt,Re,OMG,NDX,NDY,EPS,ITER)
        NITER = NITER + ITER
*   Compute U,V
        OVER = 0.0
*    Lower-Y Area
        do j=1,NY1-1
          do i=1,NX
            U(i,j) = U(i,j) - dt*( (U(i+1,j)**2 - U(i-1,j)**2)*dx
     1             + (U(i,j+1)*V(i,j+1) - U(i,j-1)*V(i,j-1))*dy
     2             + (P(i+1,j) - P(i-1,j))*dx
     3             + ( (2.0*U(i,j) - U(i-1,j) - U(i+1,j))*ddx
     4             + (2.0*U(i,j) - U(i,j-1) - U(i,j+1))*ddy )/Re )
            V(i,j) = V(i,j) - dt*( (V(i,j+1)**2 - V(i,j-1)**2)*dy
     1             + (U(i+1,j)*V(i+1,j) - U(i-1,j)*V(i-1,j))*dx
     2             + (P(i,j+1) - P(i,j-1))*dy
     3             + ( (2.0*V(i,j) - V(i-1,j) - V(i+1,j))*ddx
     4             + (2.0*V(i,j) - V(i,j-1) - V(i,j+1))*ddy )/Re )
            OVER   = OVER + abs(U(i,j)) + abs(V(i,j))
          end do
        end do
*    Middle-Y Area
        do j=NY1,NY2
          do i=1,NX1-1
            U(i,j) = U(i,j) - dt*( (U(i+1,j)**2 - U(i-1,j)**2)*dx
     1             + (U(i,j+1)*V(i,j+1) - U(i,j-1)*V(i,j-1))*dy
     2             + (P(i+1,j) - P(i-1,j))*dx
     3             + ( (2.0*U(i,j) - U(i-1,j) - U(i+1,j))*ddx
     4             + (2.0*U(i,j) - U(i,j-1) - U(i,j+1))*ddy )/Re )
            V(i,j) = V(i,j) - dt*( (V(i,j+1)**2 - V(i,j-1)**2)*dy
     1             + (U(i+1,j)*V(i+1,j) - U(i-1,j)*V(i-1,j))*dx
     2             + (P(i,j+1) - P(i,j-1))*dy
     3             + ( (2.0*V(i,j) - V(i-1,j) - V(i+1,j))*ddx
     4             + (2.0*V(i,j) - V(i,j-1) - V(i,j+1))*ddy )/Re )
            OVER   = OVER + abs(U(i,j)) + abs(V(i,j))
          end do
          do i=NX2+1,NX
            U(i,j) = U(i,j) - dt*( (U(i+1,j)**2 - U(i-1,j)**2)*dx
     1             + (U(i,j+1)*V(i,j+1) - U(i,j-1)*V(i,j-1))*dy
     2             + (P(i+1,j) - P(i-1,j))*dx
     3             + ( (2.0*U(i,j) - U(i-1,j) - U(i+1,j))*ddx
     4             + (2.0*U(i,j) - U(i,j-1) - U(i,j+1))*ddy )/Re )
            V(i,j) = V(i,j) - dt*( (V(i,j+1)**2 - V(i,j-1)**2)*dy
     1             + (U(i+1,j)*V(i+1,j) - U(i-1,j)*V(i-1,j))*dx
     2             + (P(i,j+1) - P(i,j-1))*dy
     3             + ( (2.0*V(i,j) - V(i-1,j) - V(i+1,j))*ddx
     4             + (2.0*V(i,j) - V(i,j-1) - V(i,j+1))*ddy )/Re )
            OVER   = OVER + abs(U(i,j)) + abs(V(i,j))
          end do
        end do
*    Upper-Y Area
        do j=NY2+1,NY-1
          do i=1,NX
            U(i,j) = U(i,j) - dt*( (U(i+1,j)**2 - U(i-1,j)**2)*dx
     1             + (U(i,j+1)*V(i,j+1) - U(i,j-1)*V(i,j-1))*dy
     2             + (P(i+1,j) - P(i-1,j))*dx
     3             + ( (2.0*U(i,j) - U(i-1,j) - U(i+1,j))*ddx
     4             + (2.0*U(i,j) - U(i,j-1) - U(i,j+1))*ddy )/Re )
            V(i,j) = V(i,j) - dt*( (V(i,j+1)**2 - V(i,j-1)**2)*dy
     1             + (U(i+1,j)*V(i+1,j) - U(i-1,j)*V(i-1,j))*dx
     2             + (P(i,j+1) - P(i,j-1))*dy
     3             + ( (2.0*V(i,j) - V(i-1,j) - V(i+1,j))*ddx
     4             + (2.0*V(i,j) - V(i,j-1) - V(i,j+1))*ddy )/Re )
            OVER   = OVER + abs(U(i,j)) + abs(V(i,j))
          end do
        end do
*   Check Divergent
        if(OVER.gt.1.0D10) then
          WRITE(6,*) '** Stop for over flow computation **'
          WRITE(6,*) '  You have to give smaller DT'
          STOP
        end if
*   Output U,V,Phi
        if(MOD(k,MT).eq.0) then
          WRITE(6,150) T,k,NITER
          NITER = 0
          CALL OUTUVP(P,U,V,PHI,hx,hy,NDX,NDY)
          if(ID.lt.9999) ID = ID + 1
        end if
      end do
      CALL XCLOCK(T2,5)
      WRITE(6,200) NX,NT,T2-T1 
*
      CALL WINDOW_CLOSE(GFX_WINDOW)
*
      STOP
  100 FORMAT('# Flow around Square a Pillar Numerical Analysis',/,
     1 '# XM=',F8.1,'  NX1,NX2,NX=',3I4)
  110 FORMAT('# YM=',F8.1,'  NY1,NY2,NY=',3I4)
  120 FORMAT('# Re=',F8.1,'  DT=',F10.6,'  NT,MT=',2I10)
  150 FORMAT('# Time=',F10.6,'  Step=',I10,'  SOR Loops=',I10) 
  200 FORMAT(1H ,' NX,NT,Time(s)=',2I10,F10.3) 
      END
*=================================================================*
      SUBROUTINE PSOL(P,A,B,U,V,hx,hy,dt,Re,OMG,NDX,NDY,EPS,ITER)
*=================================================================*
*  Solve Ax=b by SOR with 2 dimensional FDM                       *
*    Solve P by U,V with -div(P)=f(U,V)                           *
*-----------------------------------------------------------------*
*    P(-1:NDX,-1:NDY)   R*8, I/O, P vector                        *
*    A(-1:NDX,-1:NDY,5) R*8, Wk,  Matrix A for -div(PHI)=0        *
*    B(-1:NDX,-1:NDY)   R*8, Wk,  Right Vector for -div(PHI)=0    *
*    U(-1:NDX,-1:NDY)   R*8, In,  U vector                        *
*    V(-1:NDX,-1:NDY)   R*8, In,  V vector                        *
*    hx              R*8, In.  Delta x                            *
*    hy              R*8, In,  Delta y                            *
*    dt              R*8, In,  Delta t                            *
*    Re              R*8, In,  Re Number                          *
*    OMG             R*8, In,  Acceleration parameter for SOR     *
*    NDX             I*4, In,  First Array Size                   *
*    NDY             I*4, In,  Second Array Sixe                  *
*    EPS             R*8, In,  if ||r||/||b|| <= EPS --> return   *
*    ITER            I*4, Out, Number of Iteration                *
*-----------------------------------------------------------------*
*    Written by Yasunori Ushiro,   2003/09/14                     *
*        ( Hitachi Ltd. and Waseda University )                   *
*=================================================================*
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION U(-1:NDX,-1:NDY), V(-1:NDX,-1:NDY)
      DIMENSION A(-1:NDX,-1:NDY,5), B(-1:NDX,-1:NDY)
      DIMENSION P(-1:NDX,-1:NDY)
      COMMON /MESH/NX,NX1,NX2,NY,NY1,NY2
*  Set Value
      DYX = hy/hx
      DXY = hx/hy
      DHX = 1.0/(2.0*hx)
      DHY = 1.0/(2.0*hy)
*  Set Outer Boundary U,V,P
      do i=-1,NX+1
        P(i,-1)   = P(i,1)
        P(i,NY+1) = P(i,NY-1)
        U(i,-1)   = U(i,0)
        V(i,-1)   = V(i,0)
        U(i,NY+1) = U(i,NY)
        V(i,NY+1) = V(i,NY)
      end do 
      do j=-1,NY+1
*   P=0 on L3
        P(NX,j)   = 0.0
        P(-1,j)   = P(1,j)
        P(NX+1,j) = P(NX-1,j)
        U(-1,j)   = U(0,j)
        V(-1,j)   = V(0,j)
        U(NX+1,j) = U(NX,j)
        V(NX+1,j) = V(NX,j)
      end do
*  Set A and B
      BN = 0.0
      do j=0,NY
        do i=0,NX-1
*    Inner
          A1 = -DXY
          A2 = -DYX
          A3 = 2.0*(DXY + DYX)
          A4 = -DYX
          A5 = -DXY 
*    on B1
          if(i.eq.NX1 .and. j.ge.NY1 .and. j.le.NY2) then
            A3  = A3 - DYX
            A4  = 0.0
            UP0 = 0.0
            VP0 = 0.0
          else
            UP0 = U(i+1,j)
            VP0 = V(i+1,j)
          end if
*    on B2
          if(j.eq.NY1 .and. i.ge.NX1 .and. i.le.NX2) then
            A3  = A3 - DXY
            A5  = 0.0
            U0P = 0.0
            V0P = 0.0
          else
            U0P = U(i,j+1)
            V0P = V(i,j+1)
          end if
*    on B3
          if(i.eq.NX2 .and. j.ge.NY1 .and. j.le.NY2) then
            A2  = 0.0
            A3  = A3 - DYX
            UM0 = 0.0
            VM0 = 0.0
          else
            UM0 = U(i-1,j)
            VM0 = V(i-1,j)
          end if
*    on B4
          if(j.eq.NY2 .and. i.ge.NX1 .and. i.le.NX2) then
            A1  = 0.0
            A3  = A3 - DXY
            U0M = 0.0
            V0M = 0.0
          else
            U0M = U(i,j-1)
            V0M = V(i,j-1)
          end if
*   Set A,B
          A(i,j,1) = A1
          A(i,j,2) = A2
          A(i,j,3) = A3
          A(i,j,4) = A4
          A(i,j,5) = A5
          B(i,j) = ((UP0-UM0)**2*DYX + (V0P-V0M)**2*DXY )/4.0
     1           + (VP0-VM0)*(U0P-U0M)/2.0 
     2           - ((UP0-UM0)*hy + (V0P-V0M)*hx)/(2.0*dt)
*    in Square a Pillar
          if( (i.gt.NX1.and.i.lt.NX2) .and. 
     1        (j.gt.NY1.and.j.lt.NY2) ) then
            A(i,j,1) = 0.0
            A(i,j,2) = 0.0
            A(i,j,3) = 1.0
            A(i,j,4) = 0.0
            A(i,j,5) = 0.0
            B(i,j)   = P(NX1,NY1)
          end if
          BN = BN + (B(i,j)/A(i,j,3))**2
        end do
      end do
*  Solve Ax=b
      do k=1,ITER
        RN = 0.0
!$OMP PARALLEL DO REDUCTION(+:RN) PRIVATE(i,j,R) COLLAPSE(2)
        do j=0,NY
         do i=0,NX-1
            R = ( B(i,j) - A(i,j,1)*P(i,j-1) - A(i,j,2)*P(i-1,j)
     1        - A(i,j,4)*P(i+1,j) - A(i,j,5)*P(i,j+1) )/A(i,j,3)
     2        - P(i,j)
            P(i,j) = P(i,j) + OMG*R
            RN = RN + (R/A(i,j,3))**2
          end do
        end do
*   Check Conversion
        ERR = sqrt(RN/BN)
        if(ERR.le.EPS) go to 100
      end do
  100 CONTINUE
      ITER = k
*
      RETURN
      END
*=================================================================*
      SUBROUTINE PHISOL(PHI,A,B,U,V,hx,hy,OMG,NDX,NDY,EPS,ITER)
*=================================================================*
*  Solve Ax=b by SOR with 2 dimensional FDM                       *
*    Solve PHI and Compute U,V                                    *
*    -div(PHI)=0 and d(PHI)/dx=U, d(PHI)/dy=V                     *
*-----------------------------------------------------------------*
*    PHI(-1:NDX,-1:NDY) R*8, I/O, PHI vector                      *
*    A(-1:NDX,-1:NDY,5) R*8, Wk,  Matrix A for -div(PHI)=0        *
*    B(-1:NDX,-1:NDY)   R*8, Wk,  Right Vector for -div(PHI)=0    *
*    U(-1:NDX,-1:NDY)   R*8, In,  U vector                        *
*    V(-1:NDX,-1:NDY)   R*8, In,  V vector                        *
*    hx              R*8, In.  Delta x                            *
*    hy              R*8, In,  Delta y                            *
*    OMG             R*8, In,  Acceleration parameter for SOR     *
*    NDX             I*4, In,  First Array Size                   *
*    NDY             I*4, In,  Second Array Sixe                  *
*    EPS             R*8, In,  if ||r||/||b|| <= EPS --> return   *
*    ITER            I*4, Out, Number of Iteration                *
*-----------------------------------------------------------------*
*    Written by Yasunori Ushiro,   2003/09/14                     *
*        ( Hitachi Ltd. and Waseda University )                   *
*=================================================================*
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION U(-1:NDX,-1:NDY), V(-1:NDX,-1:NDY)
      DIMENSION A(-1:NDX,-1:NDY,5), B(-1:NDX,-1:NDY)
      DIMENSION PHI(-1:NDX,-1:NDY)
      COMMON /MESH/NX,NX1,NX2,NY,NY1,NY2
*  Set Value
      DYX = hy/hx
      DXY = hx/hy
      DHX = 1.0/(2.0*hx)
      DHY = 1.0/(2.0*hy)
*  Set Initial PHI=X
      do j=0,NY
        do i=0,NX+1
          PHI(i,j) = i*hx
        end do
      end do
*  Set A and B
      BN = 0.0
      do j=1,NY-1
        do i=1,NX
*    Inner
          A1 = -DXY
          A2 = -DYX
          A3 = 2.0*(DXY + DYX)
          A4 = -DYX
          A5 = -DXY 
          BV = 0.0
*    on L3
          if(i.eq.NX) then
            A3 = A3 - DYX
            A4 = 0.0   
            BV = BV + hy
          end if
*    on B1
          if(i.eq.NX1 .and. j.ge.NY1 .and. j.le.NY2) then
            A3 = A3 - DYX
            A4 = 0.0
          end if
*    on B2
          if(j.eq.NY1 .and. i.ge.NX1 .and. i.le.NX2) then
            A3 = A3 - DXY
            A5 = 0.0
          end if
*    on B3
          if(i.eq.NX2 .and. j.ge.NY1 .and. j.le.NY2) then
            A2 = 0.0
            A3 = A3 - DYX
          end if
*    on B4
          if(j.eq.NY2 .and. i.ge.NX1 .and. i.le.NX2) then
            A1 = 0.0
            A3 = A3 - DXY
          end if
*    in Square a Pillar
          if( (i.gt.NX1.and.i.lt.NX2) .and. 
     1        (j.gt.NY1.and.j.lt.NY2) ) then
            A1 = 0.0
            A2 = 0.0
            A3 = 1.0
            A4 = 0.0
            A5 = 0.0
            BV = 0.0
          end if
*    Set A,B
          A(i,j,1) = A1
          A(i,j,2) = A2
          A(i,j,3) = A3
          A(i,j,4) = A4
          A(i,j,5) = A5
          B(i,j)   = BV
          BN       = BN + (BV/A3)**2
        end do
      end do
*  Solve Ax=b
      do k=1,ITER
        RN = 0.0
!$OMP PARALLEL DO PRIVATE(i,j,R) REDUCTION(+:RN) COLLAPSE(2)
        do j=1,NY-1
         do i=1,NX
            R = ( B(i,j) - A(i,j,1)*PHI(i,j-1) - A(i,j,2)*PHI(i-1,j)
     1        - A(i,j,4)*PHI(i+1,j) - A(i,j,5)*PHI(i,j+1) )/A(i,j,3)
     2        - PHI(i,j)
            PHI(i,j) = PHI(i,j) + OMG*R
            RN = RN + R**2
          end do
        end do
*   Check Conversion
        ERR = sqrt(RN/BN)
        if(ERR.le.EPS) go to 100
      end do
  100 CONTINUE
      ITER = k
*  Compute U,V
      do j=1,NY-1
        do i=1,NX
          U(i,j) = (PHI(i+1,j) - PHI(i-1,j))*DHX
          V(i,j) = (PHI(i,j+1) - PHI(i,j-1))*DHY
        end do
      end do
*   in B
      do j=NY1,NY2
        do i=NX1,NX2
          U(i,j) = 0.0
          V(i,j) = 0.0
        end do
      end do
*   on L1 Boundary
      do j=1,NY-1
        U(0,j)  = 1.0
        V(0,j)  = 0.0
      end do
*   on L2,L4 Boundary
      do i=0,NX
        U(i,0)  = 1.0
        V(i,0)  = 0.0
        U(i,NY) = 1.0
        V(i,NY) = 0.0
      end do
*
      RETURN
      END
*=================================================================*
      SUBROUTINE OUTUVP(P,U,V,OMG,hx,hy,NDX,NDY)
*=================================================================*
*  Compute PHI and Output PHI,U,V                                 *
*    OMG(i,j) = dV/dx - dU/dy                                     *
*-----------------------------------------------------------------*
*    P(0:NDX,0:NY)    R*8, In,  P vector                          *
*    U(0:NDX,0:NY)    R*8, In,  U vector                          *
*    V(0:NDX,0:NY)    R*8, In,  V vector                          *
*    OMG(0:NDX,0:NDY) R*8, Wk,  Vorticity Vector                  *
*    hx               R*8, In,  Delta x                           *
*    hy               R*8, In,  Delta y                           *
*    NDX              I*4, In,  First Array Size of P,U,V         *
*    NDY              I*4, In,  Second Array Size of P,U,V        *
*-----------------------------------------------------------------*
*    Written by Yasunori Ushiro,   2003/09/14                     *
*        ( Hitachi Ltd. and Waseda University )                   *
*=================================================================*
!     USE libpixmap_core
      USE libpixmap_window
      USE libpixmap_palette
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION P(-1:NDX,-1:NDY), OMG(-1:NDX,-1:NDY)
      DIMENSION U(-1:NDX,-1:NDY), V(-1:NDX,-1:NDY)
      COMMON /MESH/NX,NX1,NX2,NY,NY1,NY2
      TYPE(WINDOW)::GFX_WINDOW
      TYPE(PIXEL)::COLOR
      COMMON/GFX/GFX_WINDOW
      INTEGER,PARAMETER::X_FACTOR=6,Y_FACTOR=3
      REAL*8,PARAMETER::PMIN=-50.D0,PMAX=50.D0,UV_FACTOR=30.D0
!<<<
      LOGICAL,EXTERNAL::ESC_IS_PUSHED
!>>>
*
      IROUND(X) =INT(X+0.5)
*   Set Omega
      do j=0,NY
        do i=0,NX
          OMG(i,j) = (V(i+1,j)-V(i-1,j))/hx - (U(i,j+1)-U(i,j-1))/hy
        end do
      end do
*   Output
* pressure (=coloring field)
      do j=0,NY
        do i=0,NX
           if(U(i,j) .ne. 0.D0 .or. V(i,j) .ne. 0.D0) then
              COLOR=PALETTE(IDL2_BLUE_RED,PMIN,PMAX,OMG(i,j))
           else
              COLOR=PIXEL_SET_NAMED_COLOR('black')
           endif
           CALL WINDOW_CLEAR_SUBIMAGE(GFX_WINDOW,COLOR,
     &                 X_FACTOR*i,Y_FACTOR*j,X_FACTOR,Y_FACTOR)
        end do
      end do
* velocity (=vector field)
      COLOR=PIXEL_SET_NAMED_COLOR('white')
      do j=3,NY,6
        do i=0,NX,6
           if(U(i,j) .ne. 0.D0 .or. V(i,j) .ne. 0.D0) then
              ii=X_FACTOR*i
              jj=Y_FACTOR*j
              ie=IROUND(ii+UV_FACTOR*U(i,j))
              je=IROUND(jj+UV_FACTOR*V(i,j))
              dl=UV_FACTOR*DSQRT(U(i,j)*U(i,j)+V(i,j)*V(i,j))
              iw=IROUND(0.3*dl)
              is=IROUND(0.5*dl)
              CALL WINDOW_DRAW_ARROW(GFX_WINDOW,COLOR,
     &                            FALSE,TRUE,AH_TYPE5,iw,is,ii,jj,ie,je)
           end if
        end do
      end do
!<<<
!     CALL WINDOW_DISCARD_INPUTS(GFX_WINDOW)
!===
      IF (ESC_IS_PUSHED(GFX_WINDOW)) THEN
         CALL WINDOW_CLOSE(GFX_WINDOW)
         STOP
      END IF
!>>>
      CALL WINDOW_UPDATE_IMAGE(GFX_WINDOW)
*
      RETURN
      END
!------------------------------------------------------------------
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
*=================================================================*
      SUBROUTINE XCLOCK(CPU,ID)
*=================================================================*
*   CPU time Subroutine                                           *
*     CPU     R*8  Out, CPU Time                                  *
*     ID      I*4  In,  Dummy ( Same Hitachi FORTRAN XCLOCK )     *
*-----------------------------------------------------------------*
*  Written by Y. Ushiro ( Waseda and Hitachi )  2002.10.29        *
*=================================================================*
      REAL*4 TA(2),ETIME
      REAL*8 CPU
*
      IF(ID.GE.1) THEN
        CPU = ETIME(TA)
      END IF
*
      RETURN
      END

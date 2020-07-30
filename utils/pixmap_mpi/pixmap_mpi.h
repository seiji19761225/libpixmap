/*
 * pixmap_mpi.h: libpixmap APIs for MPI parallel processing
 * (c)2014-2015 Seiji Nishimura
 * $Id: pixmap_mpi.h,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#ifndef __PIXMAP_MPI_H__
#define __PIXMAP_MPI_H__

#include <mpi.h>
#include <pixmap.h>

#ifdef __PIXMAP_MPI_INTERNAL__
#define  PIXMAP_MPI_API
#else
#define  PIXMAP_MPI_API	extern
#endif

// prototypes ----------------------------------------------------------
PIXMAP_MPI_API void pixmap_mpi_deep_copy (pixmap_t *, int, MPI_Comm);
PIXMAP_MPI_API void pixmap_mpi_update    (pixmap_t *, int, MPI_Comm);
PIXMAP_MPI_API void pixmap_mpi_update_all(pixmap_t *,      MPI_Comm);

#undef  PIXMAP_MPI_API
#endif

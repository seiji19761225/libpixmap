/*
 * pixmap_mpi.c: libpixmap APIs for MPI parallel processing
 * (c)2014-2015 Seiji Nishimura
 * $Id: pixmap_mpi.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "pixmap_mpi_internal.h"

//======================================================================
void pixmap_mpi_deep_copy(pixmap_t *pixmap, int root, MPI_Comm comm)
{				// deep copy of a pixmap
    int myrank, width, height;

    MPI_Bcast(pixmap, sizeof(pixmap_t), MPI_BYTE, root, comm);
    MPI_Comm_rank(comm, &myrank);

    pixmap_get_size(pixmap, &width, &height);

    if (myrank != root)		// Non-root PEs have not allocated pixmap yet.
	pixmap_create(pixmap, width, height);

    MPI_Bcast(pixmap->data, width * height * sizeof(pixel_t),
	      MPI_BYTE, root, comm);

    return;
}

//----------------------------------------------------------------------
void pixmap_mpi_update(pixmap_t *pixmap, int root, MPI_Comm comm)
{				// update a distributed pixmap on root PE (assume untouched pixels are initialized with black).
    int myrank, width, height;

    MPI_Comm_rank(comm, &myrank);

    pixmap_get_size(pixmap, &width, &height);

    if (myrank == root)
	MPI_Reduce(MPI_IN_PLACE, pixmap->data, width * height * sizeof(pixel_t),
		   MPI_BYTE, MPI_BOR, root, comm);
    else
	MPI_Reduce(pixmap->data, NULL        , width * height * sizeof(pixel_t),
		   MPI_BYTE, MPI_BOR, root, comm);

    return;
}

//----------------------------------------------------------------------
void pixmap_mpi_update_all(pixmap_t *pixmap, MPI_Comm comm)
{				// update a distributed pixmap on all PEs (assume untouched pixels are initialized with black).
    int width, height;

    pixmap_get_size(pixmap, &width, &height);

    MPI_Allreduce(MPI_IN_PLACE, pixmap->data, width * height * sizeof(pixel_t),
		  MPI_BYTE, MPI_BOR, comm);

    return;
}

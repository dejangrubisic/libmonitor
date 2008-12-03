/*
 *  Override mpi_comm_rank_ in Fortran.
 *
 *  $Id$
 */

#include "config.h"
#include "common.h"
#include "monitor.h"

typedef void mpi_comm_fcn_t(int *, int *, int *);
#ifdef MONITOR_STATIC
extern mpi_comm_fcn_t  mpi_comm_size_;
extern mpi_comm_fcn_t  __real_mpi_comm_rank_;
#endif
static mpi_comm_fcn_t  *real_mpi_comm_size = NULL;
static mpi_comm_fcn_t  *real_mpi_comm_rank = NULL;

/*
 * In Fortran, MPI_Comm is always int.
 */
void
MONITOR_WRAP_NAME(mpi_comm_rank_)(int *comm, int *rank, int *ierror)
{
    int size = -1;

    MONITOR_GET_REAL_NAME(real_mpi_comm_size, mpi_comm_size_);
    MONITOR_GET_REAL_NAME_WRAP(real_mpi_comm_rank, mpi_comm_rank_);
    (*real_mpi_comm_size)(comm, &size, ierror);
    (*real_mpi_comm_rank)(comm, rank, ierror);
    MONITOR_DEBUG("setting size = %d, rank = %d\n", size, *rank);
    monitor_set_mpi_size_rank(size, *rank);
}

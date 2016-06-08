#include <stdio.h>
#include "mpi.h"

void matmul_summa_a(double * matA, double * matB, double * matC, int localDim, \
	                 int mycoords[], int dimProc[],int myid2d , MPI_Comm comm2d);
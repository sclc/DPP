//
#include <stdio.h>
#include <mpi.h>
#include "matmul.ijk.h"

void matmul_cannon_a(double * matA, double * matB, double * matC, int localDim, \
	                 int mycoords[], int dimProc[],int myid2d , MPI_Comm comm2d);

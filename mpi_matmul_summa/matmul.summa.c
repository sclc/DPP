#include "matmul.summa.h"
// #define DB_SUMMA_1
// #define DB_SUMMA_2

void matmul_summa_a(double * matA, double * matB, double * matC, int localDim, \
	                 int mycoords[], int dimProc[],int myid2d , MPI_Comm comm2d)
{
	int matSize = localDim * localDim;
	double *Abuffer , *Bbuffer;
	int ierr;
	MPI_Comm comm1dA, comm1dB;
	int remainDimsA[] = {0,1};
	int remainDimsB[] = {1,0}; 
	int Amyrank2d_1d, Bmyrank2d_1d;
	int idxK;

	// int MPI_Cart_sub ( MPI_Comm comm, int *remain_dims, MPI_Comm *comm_new )

	ierr = MPI_Cart_sub ( comm2d, remainDimsA, &comm1dA);
	ierr = MPI_Cart_sub ( comm2d, remainDimsB, &comm1dB);

	ierr =MPI_Comm_rank(comm1dA, &Amyrank2d_1d); 
	ierr =MPI_Comm_rank(comm1dB, &Bmyrank2d_1d); 

	Abuffer = (double*)calloc(dimProc[0] * matSize, sizeof(double));
	Bbuffer = (double*)calloc(dimProc[1] * matSize, sizeof(double));
#ifdef DB_SUMMA_1
	printf ("myid2d:%d, Amyrank2d_1d:%d, Bmyrank2d_1d:%d\n", myid2d, Amyrank2d_1d, Bmyrank2d_1d);
#endif

// int MPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
//                   void *recvbuf, int recvcount, MPI_Datatype recvtype,
//                   MPI_Comm comm)
	ierr = MPI_Allgather((void*)matA, matSize, MPI_DOUBLE, \
                  Abuffer, matSize, MPI_DOUBLE,comm1dA);
	ierr = MPI_Allgather((void*)matB, matSize, MPI_DOUBLE, \
                  Bbuffer, matSize, MPI_DOUBLE,comm1dB);

	int offset;
	for (idxK =0; idxK<dimProc[0]; idxK++)
	{
		offset = idxK * matSize;
		matmul_ijk_ABoffset (Abuffer, Bbuffer, matC ,localDim, offset);
	}
#ifdef DB_SUMMA_2
	MPI_Barrier(MPI_COMM_WORLD);
	int db_idx_summa;
	printf ("\n\n");
	for (db_idx_summa = 0; db_idx_summa<matSize; db_idx_summa++)
	{
		printf ("myid2d:%d, %lf", myid2d, matC[db_idx_summa]);
	}
	printf ("\n\n");
#endif

	free(Abuffer);
	free(Bbuffer);
}
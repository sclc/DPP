//
#include "matmul.cannon.h"
// #define DB_CANNON_1
// #define DB_CANNON_2
// #define DB_CANNON_3

void matmul_cannon_a(double * matA, double * matB, double * matC, int localDim, \
	                 int mycoords[], int dimProc[],int myid2d , MPI_Comm comm2d)
{
	MPI_Status status; 
	int sourceId, destId;
	int sourceIdA, destIdA, sourceIdB, destIdB;
	int localSize = localDim * localDim;
	int idx;
	
	// int MPI_Sendrecv_replace(void *buf, int count, MPI_Datatype datatype, 
 //                       int dest, int sendtag, int source, int recvtag,
 //                       MPI_Comm comm, MPI_Status *status)

	MPI_Cart_shift(comm2d, 1, -mycoords[0], &sourceId, &destId); 
#ifdef DB_CANNON_3
	MPI_Barrier(MPI_COMM_WORLD);
	printf("myid2d:%d, sourceId:%d, destId:%d\n", myid2d, sourceId,destId);
#endif
	MPI_Sendrecv_replace((void*)matA, localSize, MPI_DOUBLE, destId, \
	    1, sourceId, 1, comm2d, &status); 
	
#ifdef DB_CANNON_1
	MPI_Barrier(MPI_COMM_WORLD);
	int idx_db;
	printf("\n");
	for (idx_db=0; idx_db<localSize; idx_db++)
	{
		printf ("CannonMyid2d:%d, %lf \t",myid2d, matA[idx_db]);
	}
	printf("\n");
	
#endif
	MPI_Cart_shift(comm2d, 0, -mycoords[1], &sourceId, &destId); 
	MPI_Sendrecv_replace((void*)matB, localSize, MPI_DOUBLE, destId, \
	    1, sourceId, 1, comm2d, &status); 

#ifdef DB_CANNON_2
	MPI_Barrier(MPI_COMM_WORLD);
	int idx_db;
	printf("\n");
	for (idx_db=0; idx_db<localSize; idx_db++)
	{
		printf ("CannonMyid2d:%d, %lf \t",myid2d, matB[idx_db]);
	}
	printf("\n");
	
#endif

	MPI_Cart_shift(comm2d, 1, -1, &sourceIdA, &destIdA); 
	MPI_Cart_shift(comm2d, 0, -1, &sourceIdB, &destIdB); 

	matmul_ijk (matA,matB,matC, localDim); 

	for (idx=1; idx<dimProc[0]; idx++) 
	{ 

		MPI_Sendrecv_replace(matA, localSize, MPI_DOUBLE, 
		    destIdA, 1, sourceIdA, 1, comm2d, &status); 

		MPI_Sendrecv_replace(matB, localSize, MPI_DOUBLE, 
		    destIdB, 1, sourceIdB, 1, comm2d, &status); 

		matmul_ijk (matA,matB,matC, localDim);
	} 

}

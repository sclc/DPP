#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mpi.h"
#include "mat.generator.h"
#include "matmul.ijk.h"
#include "matmul.cannon.h"

// #define DEBUG_MPI_1
// #define DEBUG_MPI_2
// #define DEBUG_MPI_3
// #define DEBUG_MPI_4
#define DEBUG_MPI_5

// EXP_ITER 1 :give correct result
// EXP_ITER > 1 : for profiling 
#define EXP_ITER 1


int main (int argc, char** argv)
{
	int ierr;
	int dim, numRowPerProc, matGlobalSize, matLocalSize;
	srand (time(NULL));

    ierr = MPI_Init(&argc, &argv);

    int numprocs, myid, myid2d;
    int dimProc[2], periods[2], mycoords[2];
    MPI_Comm comm2d; 

    double * matGlobalA, * matGlobalB, * matGlobalC; 
    double * matLocalA,  * matLocalB, * matLocalC;
    double * matGlobalPackingBufferA, * matGlobalPackingBufferB; 

    double t1, t2, timeSum=0.0, reducedTime;
    int idx_iter;

	if (argc<2)
	{
		printf("you need at lesast one argument for us to decide the dimension of the matrix\n");
		printf("tell us how many rows(columns) you need on each process\n");
		exit(0);
	}

	numRowPerProc = atoi(argv[1]);

#ifdef DEBUG_MPI_1
	printf("numRowPerProc = %d\n",numRowPerProc);
#endif

	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &numprocs);


	/* Set up the Cartesian topology */ 
	dimProc[0] = dimProc[1] = (int)sqrt(numprocs);

	/* Set the periods for wraparound connections */ 
	periods[0] = periods[1] = 1; 

	/* Create the Cartesian topology, with rank reordering */ 
	MPI_Cart_create(MPI_COMM_WORLD, 2, dimProc, periods, 1, &comm2d); 
    
	/* Get the rank and coordinates with respect to the new topology */ 
	MPI_Comm_rank(comm2d, &myid2d); 
	MPI_Cart_coords(comm2d, myid2d, 2, mycoords); 

#ifdef DEBUG_MPI_2
	printf ("myid:%d, myid2d: %d, mycoords[0]: %d, mycoords[1]: %d\n",\
		     myid,    myid2d,     mycoords[0],     mycoords[1]);

	int leftrank, rightrank, uprank, downrank;
	/* Compute ranks of the up and left shifts */ 
	MPI_Cart_shift(comm2d, 1, 1, &leftrank, &rightrank); 
	MPI_Cart_shift(comm2d, 0, 1, &uprank, &downrank); 

	printf ("myid2d: %d, rightrank:%d, leftrank:%d, uprank:%d, downrank:%d\n", \
		     myid2d    , rightrank   , leftrank   , uprank   , downrank   );

#endif

    dim = numRowPerProc * (int)sqrt(numprocs);

#ifdef DEBUG_MPI_1
	printf("dim = %d\n",dim);
#endif

	matGlobalSize = dim * dim;
	matLocalSize = numRowPerProc * numRowPerProc;

	matLocalA = (double*)calloc (matLocalSize, sizeof(double));
	matLocalB = (double*)calloc (matLocalSize, sizeof(double));
	matLocalC = (double*)calloc (matLocalSize, sizeof(double));

	if (myid == 0)
	{
		matGlobalA = (double *) calloc (matGlobalSize, sizeof(double));
		matGlobalB = (double *) calloc (matGlobalSize, sizeof(double));
		matGlobalC = (double *) calloc (matGlobalSize, sizeof(double));
		matGlobalPackingBufferA = (double *) calloc (matGlobalSize, sizeof(double));
		matGlobalPackingBufferB = (double *) calloc (matGlobalSize, sizeof(double));

		if (matGlobalA == NULL || matGlobalB == NULL || matGlobalC == NULL \
			|| matGlobalPackingBufferA==NULL || matGlobalPackingBufferB==NULL)
		{
			printf ("matGlobal creating faliure\n");
			exit(0);
		}

		// GenerateGlobalRandomColmajor (matGlobalA, matGlobalSize, 1.0, 0.0);
		// GenerateGlobalRandomColmajor (matGlobalB, matGlobalSize, 1.0, 0.0);
		GenerateParallelRandomColmajorUnifromVals (matGlobalA, matGlobalSize, 2.0);
		GenerateParallelRandomColmajorUnifromVals (matGlobalB, matGlobalSize, 6.0);

		// packing data for distribution
		// X: row, Y:col
		int idxProcX, idxProcY, idxLocalX, idxLocalY;
		int idxOriginal, idxNew;

		for (idxProcY =0; idxProcY < dimProc[1]; idxProcY++)
		{
			for (idxProcX =0; idxProcX< dimProc[0]; idxProcX++)
			{
				for (idxLocalY =0; idxLocalY<numRowPerProc; idxLocalY++)
				{
					for (idxLocalX =0; idxLocalX < numRowPerProc; idxLocalX++)
					{
						idxOriginal = idxProcY * dimProc[1] * matLocalSize \
						            + idxLocalY * dim + idxProcX * numRowPerProc + idxLocalX;
						idxNew = (idxProcX * dimProc[0] + idxProcY) * matLocalSize \
						       + idxLocalY * numRowPerProc + idxLocalX; 
#ifdef DEBUG_MPI_3
						printf("idxOriginal: %d, idxNew:%d\n",idxOriginal, idxNew);
#endif
						matGlobalPackingBufferA[idxNew] = matGlobalA[idxOriginal];
						matGlobalPackingBufferB[idxNew] = matGlobalB[idxOriginal];
					}
				}
			}
		}

	}


// int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
//                void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
//                MPI_Comm comm)
	ierr = MPI_Scatter ((void*) matGlobalPackingBufferA, matLocalSize, MPI_DOUBLE, \
		                (void*) matLocalA, matLocalSize, MPI_DOUBLE, 0, comm2d);

	ierr = MPI_Scatter ((void*) matGlobalPackingBufferB, matLocalSize, MPI_DOUBLE, \
		                (void*) matLocalB, matLocalSize, MPI_DOUBLE, 0, comm2d);

#ifdef DEBUG_MPI_3
	int idx_db;
	if (myid ==0)
	{
		// for (idx_db =0; idx_db<matGlobalSize; idx_db++)
		// {
		// 	printf("%lf \t", matGlobalA[idx_db]);
		// }
		// printf("\n\n");
		for (idx_db =0; idx_db<matGlobalSize; idx_db++)
		{
			printf("%lf \t", matGlobalB[idx_db]);
		}
		printf("\n\n");
	}
	MPI_Barrier(MPI_COMM_WORLD);

	// for (idx_db=0; idx_db<matLocalSize; idx_db++)
	// {
	// 	printf("myid2d:%d, %lf \t", myid2d, matLocalA[idx_db]);
	// }
	// printf("\n");
	for (idx_db=0; idx_db<matLocalSize; idx_db++)
	{
		printf("myid2d:%d, %lf \t", myid2d, matLocalB[idx_db]);
	}
	printf("\n");
#endif

#ifdef DEBUG_MPI_4
	if (myid == 0)
	{
		matmul_ijk(matGlobalA, matGlobalB, matGlobalC, dim);
	
		int db_matmul_idx;
		printf("\n");
		for (db_matmul_idx = 0; db_matmul_idx < matGlobalSize; db_matmul_idx++)
		{
			printf ("%lf\t", matGlobalA[db_matmul_idx]);
		}
		printf("\n\n");
		for (db_matmul_idx = 0; db_matmul_idx < matGlobalSize; db_matmul_idx++)
		{
			printf ("%lf\t", matGlobalB[db_matmul_idx]);
		}
		printf("\n\n");
		for (db_matmul_idx = 0; db_matmul_idx < matGlobalSize; db_matmul_idx++)
		{
			printf ("%lf\t", matGlobalC[db_matmul_idx]);
		}
		printf("\n\n");
	}

#endif

   	ierr = MPI_Barrier(MPI_COMM_WORLD);
    t1 = MPI_Wtime();

    for (idx_iter =0; idx_iter<EXP_ITER; idx_iter++)
    {
		matmul_cannon_a(matLocalA, matLocalB, matLocalC, numRowPerProc, \
	    	            mycoords, dimProc, myid2d , comm2d);
	}

    ierr = MPI_Barrier(MPI_COMM_WORLD);
    t2 = MPI_Wtime();
    timeSum+= t2 - t1;
    timeSum /= (double) EXP_ITER;

// int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype,
//                MPI_Op op, int root, MPI_Comm comm)
    ierr = MPI_Reduce(&timeSum, &reducedTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (myid == 0)
    {
    	printf("%d matmul_cannon_a calls\n",EXP_ITER);
    	printf("Average time: %lf secs\n",reducedTime);
    }

#ifdef DEBUG_MPI_5

 	int db_5_matmul_idx;
 // 	if (myid == 0)
	// {
	// 	matmul_ijk(matGlobalA, matGlobalB, matGlobalC, dim);
	// 	printf("\n\n");
	// 	for (db_5_matmul_idx = 0; db_5_matmul_idx < matGlobalSize; db_5_matmul_idx++)
	// 	{
	// 		printf ("%lf\t", matGlobalC[db_5_matmul_idx]);
	// 	}
	// 	printf("\n\n");
	// }
	MPI_Barrier(MPI_COMM_WORLD);
	for (db_5_matmul_idx = 0; db_5_matmul_idx < matLocalSize; db_5_matmul_idx++)
	{
		printf ("myid2d:%d, %lf\t", myid2d, matLocalC[db_5_matmul_idx]);
	}
	printf("\n\n");
#endif
	
	if (myid == 0)
	{
		free (matGlobalA);
		free (matGlobalB);
		free (matGlobalC);
		free(matGlobalPackingBufferA);
		free(matGlobalPackingBufferB);
	}
	free (matLocalA);
	free (matLocalB);
	free (matLocalC);
	MPI_Comm_free(&comm2d);


    ierr = MPI_Finalize();

    return 0;

}

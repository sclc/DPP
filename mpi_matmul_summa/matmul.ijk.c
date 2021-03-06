#include "matmul.ijk.h"

void matmul_ijk (double * matA, double * matB, double * matC, int localDim)
{
	int idxI, idxJ, idxK;

	for (idxI = 0; idxI< localDim; idxI++)
		for (idxJ = 0; idxJ<localDim; idxJ++)
			for (idxK =0; idxK <localDim; idxK++)
			{  
				matC[idxJ * localDim + idxI] += matA[idxK * localDim + idxI]  \
				                              * matB[idxJ * localDim + idxK];
			}

}

void matmul_ijk_ABoffset (double * matA, double * matB, double * matC, int localDim, int offset)
{
	int idxI, idxJ, idxK;

	for (idxI = 0; idxI< localDim; idxI++)
		for (idxJ = 0; idxJ<localDim; idxJ++)
			for (idxK =0; idxK <localDim; idxK++)
			{
				matC[idxJ * localDim + idxI] += matA[offset + idxK * localDim + idxI]  \
				                              * matB[offset + idxJ * localDim + idxK];
			}

}
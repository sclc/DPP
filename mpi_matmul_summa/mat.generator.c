#include "mat.generator.h"

void GenerateParallelRandomColmajor  (double * matLocal, int localSize, double upper, double lower)
{
	int idx;
	double range = upper - lower;

	for (idx=0; idx<localSize; idx++)
	{
		matLocal[idx] =  lower + ((double)rand()/(double)RAND_MAX) * range;
	}

}

void GenerateGlobalRandomColmajor (double * matGlobal, int sizeGlobal, double upper, double lower)
{
	
	int idx;
	double range = upper - lower;

	for (idx=0; idx<sizeGlobal; idx++)
	{
		matGlobal[idx] =  lower + ((double)rand()/(double)RAND_MAX) * range;
	}

}

void GenerateParallelRandomColmajorUnifromVals (double * mat, int localSize, double val)
{
	int idx;

	for (idx=0; idx<localSize; idx++)
	{
		mat[idx] =  val;
	}

}
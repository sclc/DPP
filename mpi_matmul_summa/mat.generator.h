#include <stdlib.h>

void GenerateParallelRandomColmajor (double * matLocal, int localSize, double upper, double lower);

void GenerateGlobalRandomColmajor (double * matGlobal, int sizeGlobal, double upper, double lower);

void GenerateParallelRandomColmajorUnifromVals (double * mat, int localSize, double val);
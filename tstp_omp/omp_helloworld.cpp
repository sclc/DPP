#include <stdio.h>
#include <omp.h>

#ifdef __cplusplus
using namespace std;
#endif

#define NUM_THREADS 10

int main()
{	
	int nthreads, tid;

#pragma omp parallel private(tid, nthreads)
	{
		//omp_set_num_threads(NUM_THREADS);
		tid = omp_get_thread_num();
		//cout<<"hello world! and I am "<<tid<<endl;
		printf("printf ver. hello world. I am %d\n", tid);

		// nthreads=omp_get_num_threads();
		// tid == 0? printf("printf ver. Total threasds %d\n",nthreads): printf("%d\n",tid);
		if (tid==0)
		{
			nthreads=omp_get_num_threads();
			//cout<<"Total "<<nthreads<<" threads"<<endl;
			printf("printf ver. Total threasds %d\n",nthreads);
		}
	}
	
	return 0;
}
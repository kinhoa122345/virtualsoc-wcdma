#include "fir.h"


void fir ( int* filter, int filterSize, int* dataI, int* dataQ, int dataSize, int* resultI, int* resultQ )
{
	// in reality data is a tab of dataSize + filterSize elements beacause we need all these old datas to calculate all the new results (dataSize elements)
	int i, j ;

	#pragma omp parallel
	{
		int myId = omp_get_thread_num();
		if(myId == 1)
		{
			parallelFir(filter, filterSize, dataI, dataSize, resultI);
		}
		else if(myId == 2)
		{
			parallelFir(filter, filterSize, dataQ, dataSize, resultQ);
		}
		
	}

	/*if(num_proc == 1)
	{
		for ( i = 0 ; i < dataSize ; i++ )
		{
			resultI[i] = 0;

			for ( j = 0; j < filterSize ; j++ )
			{
				int dataIndex = i + filterSize - j;
				resultI[i] += filter[j] * dataI[dataIndex];
			}
		}
		RELEASE_LOCK(0);
	}
	else if(num_proc == 2)
	{
		for ( i = 0 ; i < dataSize ; i++ )
		{
			resultQ[i] = 0;

			for ( j = 0; j < filterSize ; j++ )
			{
				int dataIndex = i + filterSize - j;
				resultQ[i] += filter[j] * dataQ[dataIndex];
			}
		}
		RELEASE_LOCK(1);
	}
	WAIT(0);
	WAIT(1);*/
	
	return;
}

void parallelFir(int* filter, int filterSize, int* data, int dataSize, int* result)
{
	for ( i = 0 ; i < dataSize ; i++ )
	{
		result[i] = 0;

		for ( j = 0; j < filterSize ; j++ )
		{
			int dataIndex = i + filterSize - j;
			result[i] += filter[j] * data[dataIndex];
		}
	}
}

#include "fir.h"


void fir( int* filter, int filterSize, int* dataI, int* dataQ, int dataSize, int* resultI, int* resultQ )
{
	// in reality data is a tab of dataSize + filterSize elements beacause we need all these old datas to calculate all the new results (dataSize elements)
	//int i, j ;

	int i;
	_printdecn("thread : ", (int) ( omp_get_thread_num() ));
	
	/*for(i = 0 ; i<100 ; i++)
		_printdecn("myId ", (int) (omp_get_thread_num() ));*/
	//#pragma omp parallel for num_threads(2)
	/*for(i = 0 ; i<10 ; i++)
	{
		//int myId = omp_get_thread_num();
		//_printdecn("myId ", (int) ( myId ));
		parallelFir(filter, filterSize, dataI, dataSize, resultI);
		/*if(i == 0)
		{
			parallelFir(filter, filterSize, dataI, dataSize, resultI);
		}
		else if(i == 1)
		{
			parallelFir(filter, filterSize, dataQ, dataSize, resultQ);
		}*/
		
	//}

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
	int myId = omp_get_thread_num();
	_printdecn("myId : ", (int) ( myId ));
	int i,j;

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

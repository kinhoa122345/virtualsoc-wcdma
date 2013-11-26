#include "fir.h"

void fir ( int* filter, int filterSize, int* data, int dataSize, int* result )
{
	// in reality data is a tab of dataSize + filterSize elements beacause we need all these old datas to calculate all the new results (dataSize elements)
	int i, j ;
	for ( i = 0 ; i < dataSize ; i++ )
	{
		result[i] = 0;

		for ( j = 0; j < filterSize ; j++ )
		{
			int dataIndex = i + filterSize - j;
			result[i] += filter[j] * data[dataIndex];
		}
	}
	return;
}

#include <stdlib.h>
#include <gomp/omp.h>
#include "../support/simulator/appsupport.h"

void fir(int* filter, int filterSize, int* dataI, int* dataQ, int dataSize, int* resultI, int* resultQ);
void parallelFir(int* filter, int filterSize, int* data, int dataSize, int* result)
#ifndef FIR
#define FIR

#include <stdlib.h>
#include <stdio.h>
#include "appsupport.h"
#include "omp.h"

void fir(int* filter, int filterSize, int* dataI, int* dataQ, int dataSize, int* resultI, int* resultQ);
void parallelFir(int* filter, int filterSize, int* data, int dataSize, int* result);

#endif
#include <stdlib.h>
#include "qpsk.h" 

void QPSKinv ( int* dataI, int* dataQ, int dataSize, int* result, int* amp )
{
	int i, offset ;
	offset = 0 ;
	
	*amp = dataI[0] ; 
	
	for ( i = 0 ; i < dataSize ; i += 4 , offset += 2 )
	{
		result [ offset ] = dataI [ i ] ;
		result [ offset + 1 ] = dataQ [ i ] ; 
	}
	
	return ;
}

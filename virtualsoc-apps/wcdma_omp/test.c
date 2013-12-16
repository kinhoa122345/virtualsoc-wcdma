#include <stdio.h>

#include "wcdma_signal_fixed.h"
#include "math.h"
#include "qpsk.h" 
#include "fir.h"


int main()
{
	//Local variables (declared in wcdma_signal_fixed.h)
	//int Signal_I [(SF/2*NB_SYMBOL+DELAY_MAX/2)*SAMPLING_FACTOR]
	//int Signal_Q [(SF/2*NB_SYMBOL+DELAY_MAX/2)*SAMPLING_FACTOR]
	//int FIR_COEFF[FILTER_NB_CELL]
	//int symbole_flow_user1[NB_SYMBOL]
	//int ovsf_code_user1[SF]

	//local variables (others)
	int Signal_I_symb[SF/2*SAMPLING_FACTOR];
	int Signal_Q_symb[SF/2*SAMPLING_FACTOR];

	int Signal_I_filtered[(SF/2*NB_SYMBOL+DELAY_MAX/2)*SAMPLING_FACTOR] ;
	int Signal_Q_filtered[(SF/2*NB_SYMBOL+DELAY_MAX/2)*SAMPLING_FACTOR] ;
	
	int Signal [ (SF/2*NB_SYMBOL+DELAY_MAX/2)*SAMPLING_FACTOR * 2 ] ;
	int amplitude ;

	//Other variables
	int b,i;


	//Inits
	fir ( FIR_COEFF, FILTER_NB_CELL, Signal_I, (SF/2*NB_SYMBOL+DELAY_MAX/2)*SAMPLING_FACTOR, Signal_I_filtered ) ;
	fir ( FIR_COEFF, FILTER_NB_CELL, Signal_Q, (SF/2*NB_SYMBOL+DELAY_MAX/2)*SAMPLING_FACTOR, Signal_Q_filtered ) ;
	
	QPSKinv ( Signal_I_filtered, Signal_Q_filtered, (SF/2*NB_SYMBOL+DELAY_MAX/2)*SAMPLING_FACTOR, Signal, &amplitude ) ; 
		
	for ( i = 0 ; i < (SF/2*NB_SYMBOL+DELAY_MAX/2)*SAMPLING_FACTOR*2 ; i++ )
	{
		printf ( "%d ", Signal[i] ) ;
		
		if ( i % 8 == 0 )
			printf ( "\n" ) ; 
	}	
	printf ( "\n" ) ; 
		
	//Check results
	
	//End
	return(0);
}


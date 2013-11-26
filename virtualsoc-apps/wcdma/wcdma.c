#include <simulator/appsupport.h>

#include "wcdma_signal_fixed.h"
#include "math.h"
#include "qpsk.h" 
#include "fir.h"


int main()
{
	int num_proc = get_proc_id();
	int a ; 
	
	start_metric();
	int Signal_I_symb[80]  ;
	int Signal_Q_symb[80]  ;
	for ( a = 0 ; a < 80 ; a++ )
	{
		Signal_I_symb[a] = 0 ;
		Signal_Q_symb[a] = 0 ;
	}
	

	int Signal_I_filtered[(SF/2*SAMPLING_FACTOR)]  ;
	int Signal_Q_filtered[(SF/2*SAMPLING_FACTOR)] ;
	
	for ( a = 0 ; a < (SF/2*SAMPLING_FACTOR) ; a++ )
	{
		Signal_I_filtered[a] = 0 ;
		Signal_Q_filtered[a] = 0 ;
	}
	
	int Signal [ 16 ] ;	
	for ( a = 0 ; a < 16 ; a++ )
	{
		Signal[a] = 0 ;
	}
	
	int SignalTau [6] ;

	int amplitude ;
	int cycles = 0 ;

	//Other variables
	int b, i, j ;

	if(num_proc==1)
	{	
		//For each symbol
		for(b=0;b<NB_SYMBOL;b++)
		{
			//Get first symbol
			for(i=0;i<(SF/2*SAMPLING_FACTOR);i++) 
			{
				// Shifting the old values at the beginning of the buffer
				Signal_I_symb[i]	= Signal_I_symb[i+16] ; 
				Signal_Q_symb[i]	= Signal_Q_symb[i+16] ; 
				
				Signal_I_symb[i+16]	= Signal_I_symb[i+32] ;
				Signal_Q_symb[i+16]	= Signal_Q_symb[i+32] ; 
				 
				Signal_I_symb[i+32]	= Signal_I_symb[i+48] ; 
				Signal_Q_symb[i+32]	= Signal_Q_symb[i+48] ; 
				
				Signal_I_symb[i+48]	= Signal_I_symb[i+64] ; 
				Signal_Q_symb[i+48]	= Signal_Q_symb[i+64] ;			
			
				// Put the new values at the end of the buffer	
				Signal_I_symb[i+64]		= Signal_I[i+b*SF/2*SAMPLING_FACTOR];	 
				Signal_Q_symb[i+64]		= Signal_Q[i+b*SF/2*SAMPLING_FACTOR];
			}

			//-------------------------------------- FIRST STAGE -----------------------------------------------
			//FIR for I and Q
			// pr("Time before FIR = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);
			fir ( FIR_COEFF, FILTER_NB_CELL, Signal_I_symb, (SF/2*SAMPLING_FACTOR), Signal_I_filtered ) ;  
			fir ( FIR_COEFF, FILTER_NB_CELL, Signal_Q_symb, (SF/2*SAMPLING_FACTOR), Signal_Q_filtered ) ;  
			
			for(i=0;i<(SF/2*SAMPLING_FACTOR);i++) 
			{
				_printdecn("I ", Signal_I_filtered[i]) ;
				_printdecn("Q ", Signal_Q_filtered[i]) ;
			}
			
			// pr("Time after FIR = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);
						
			//------------------------------------- SECOND STAGE -----------------------------------------------		
			//---- QPSK-1 (parallel to serial)
			// pr("Time before QPSK = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);
			for ( i = 0 ; i < (SF/2*SAMPLING_FACTOR)/2 ; i++ ) 
			{
				Signal[i] = Signal[i+(SF/2*SAMPLING_FACTOR)/2] ;
			}
			QPSKinv ( Signal_I_filtered, Signal_Q_filtered, (SF/2*SAMPLING_FACTOR)/2, &Signal[8], &amplitude ) ;
			// pr("Time after QPSK = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);		
			
			//-------------------------------------- THIRD STAGE -----------------------------------------------
			//---- Rake receiver
			// pr("Time before rake receiver = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL) ;
			SignalTau[0] = 0 ;
			SignalTau[1] = 0 ;
			SignalTau[2] = 0 ;
			SignalTau[3] = 0 ;
			SignalTau[4] = 0 ;
			SignalTau[5] = 0 ;

			for ( j = 0 ; j < SF ; j++ )
			{
				SignalTau[0] += Signal[j]*ovsf_code_user1[j] ;
				SignalTau[1] += Signal[j+1]*ovsf_code_user1[j] ;
				SignalTau[2] += Signal[j+2]*ovsf_code_user1[j] ;
				SignalTau[3] += Signal[j+3]*ovsf_code_user1[j] ;
				SignalTau[4] += Signal[j+4]*ovsf_code_user1[j] ;
				SignalTau[5] += Signal[j+5]*ovsf_code_user1[j] ;
			}			
			_printdecn("Bit ", (int) ( SignalTau[0]+SignalTau[1]+SignalTau[2]+SignalTau[3]+SignalTau[4]+SignalTau[5] > 0 ) ) ;
			// pr("Time after rake receiver= ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);
			
			#ifdef DISPLAY

			_printstrn("OK!");
			#endif
		
		/*fir ( FIR_COEFF, FILTER_NB_CELL, Signal_I, (SF/2*NB_SYMBOL+DELAY_MAX/2)*SAMPLING_FACTOR, Signal_I_filtered ) ;
		fir ( FIR_COEFF, FILTER_NB_CELL, Signal_Q, (SF/2*NB_SYMBOL+DELAY_MAX/2)*SAMPLING_FACTOR, Signal_Q_filtered ) ;

		QPSKinv ( Signal_I_filtered, Signal_Q_filtered, (SF/2*NB_SYMBOL+DELAY_MAX/2)*SAMPLING_FACTOR, Signal, &amplitude ) ; 
		
		for ( i = 0 ; i < NB_SYMBOL ; i++ )
		{
			SignalTau[0][i] = 0 ;
			SignalTau[1][i] = 0 ;
			SignalTau[2][i] = 0 ;
			SignalTau[3][i] = 0 ;
			SignalTau[4][i] = 0 ;
			SignalTau[5][i] = 0 ;

			for ( j = 0 ; j < SF ; j++ )
			{
				SignalTau[0][i] += Signal[i*SF+j]*ovsf_code_user1[j] ;
				if ( i != NB_SYMBOL-1 )
				{
					SignalTau[1][i] += Signal[i*SF+j+1]*ovsf_code_user1[j] ;
					SignalTau[2][i] += Signal[i*SF+j+2]*ovsf_code_user1[j] ;
					SignalTau[3][i] += Signal[i*SF+j+3]*ovsf_code_user1[j] ;
					SignalTau[4][i] += Signal[i*SF+j+4]*ovsf_code_user1[j] ;
					SignalTau[5][i] += Signal[i*SF+j+5]*ovsf_code_user1[j] ;
				}
			}
			SignalFin[i] = (int) ( SignalTau[0][i]+SignalTau[1][i]+SignalTau[2][i]+SignalTau[3][i]+SignalTau[4][i]+SignalTau[5][i] > 0 ) ;*/
		}

	}
	else
	{
		_printstrn("Only 1 processor is supported!");
	}
	
	stop_metric();
	//Stop metrics
	_printstrn("Done");
	//Check results
	
	//End
	return(0);
}


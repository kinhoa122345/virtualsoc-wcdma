#include "../support/simulator/appsupport.h"

#include "wcdma_signal_fixed.h"
#include "math.h"
#include "qpsk.h"
#include "fir.h"


int _app_main(int argc, char** arcg, char** env)
{
  int num_proc = get_proc_id();
  start_metric();


  register int a, iSymbol, iBuffer, iPosCode ;
  const int bufferSize = SF/2*SAMPLING_FACTOR;
  int Signal_I_symb[80];
  int Signal_Q_symb[80];
  register int bit;
  int Signal_I_filtered[bufferSize];
  int Signal_Q_filtered[bufferSize];
  int Signal [ 16 ];


  for ( a = 0 ; a < 80 ; a++ )
  {
    Signal_I_symb[a] = 0 ;
    Signal_Q_symb[a] = 0 ;
  }

  for ( a = 0 ; a < bufferSize ; a++ )
  {
    Signal_I_filtered[a] = 0 ;
    Signal_Q_filtered[a] = 0 ;
  }

  for ( a = 0 ; a < 16 ; a++ )
  {
    Signal[a] = 0 ;
  }

  if (num_proc == 1)
  {
    //For each symbol
    for(iSymbol=0;iSymbol<NB_SYMBOL;iSymbol++)
    {
      //Get first symbol
      for(iBuffer=0;iBuffer<bufferSize;iBuffer++)
      {
        // Shifting the old values at the beginning of the buffer
        Signal_I_symb[iBuffer]	= Signal_I_symb[iBuffer+16] ;
        Signal_Q_symb[iBuffer]	= Signal_Q_symb[iBuffer+16] ;

        Signal_I_symb[iBuffer+16]	= Signal_I_symb[iBuffer+32] ;
        Signal_Q_symb[iBuffer+16]	= Signal_Q_symb[iBuffer+32] ;

        Signal_I_symb[iBuffer+32]	= Signal_I_symb[iBuffer+48] ;
        Signal_Q_symb[iBuffer+32]	= Signal_Q_symb[iBuffer+48] ;

        Signal_I_symb[iBuffer+48]	= Signal_I_symb[iBuffer+64] ;
        Signal_Q_symb[iBuffer+48]	= Signal_Q_symb[iBuffer+64] ;

        // Put the new values at the end of the buffer
        Signal_I_symb[iBuffer+64]		= Signal_I[iBuffer+iSymbol*SF/2*SAMPLING_FACTOR];
        Signal_Q_symb[iBuffer+64]		= Signal_Q[iBuffer+iSymbol*SF/2*SAMPLING_FACTOR];
      }

      //-------------------------------------- FIRST STAGE -----------------------------------------------
      //FIR for I and Q
      pr("Time before FIR = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);
      fir ( FIR_COEFF, FILTER_NB_CELL, Signal_I_symb, Signal_Q_symb, bufferSize, Signal_I_filtered, Signal_Q_filtered ) ;
      //fir ( FIR_COEFF, FILTER_NB_CELL, Signal_Q_symb, bufferSize, Signal_Q_filtered ) ;
      pr("Time after FIR = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);

      //------------------------------------- SECOND STAGE -----------------------------------------------
      //---- QPSK-1 (parallel to serial)
      pr("Time before QPSK = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);
      for ( iBuffer = 0 ; iBuffer < bufferSize/2 ; iBuffer+=2 )
      {
        Signal[iBuffer] = Signal[iBuffer+bufferSize/2] ;
        /*Signal[iBuffer+bufferSize/2] = Signal_I_filtered[iBuffer*4] ;

          Signal[iBuffer+1] = Signal[iBuffer+1+bufferSize/2] ;
          Signal[iBuffer+1+bufferSize/2] = Signal_Q_filtered[iBuffer*4] ;	*/

      }
      QPSKinv ( Signal_I_filtered, Signal_Q_filtered, bufferSize/2, &Signal[8] ) ;
      pr("Time after QPSK = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);

      //-------------------------------------- THIRD STAGE -----------------------------------------------
      if ( iSymbol != 0 )
      {
        //---- Rake receiver
        pr("Time before RakeReceiver = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL) ;

        bit = 0 ;

        for ( iPosCode = 0 ; iPosCode < SF ; iPosCode++ )
        {
          bit += Signal[iPosCode]*ovsf_code_user1[iPosCode] + Signal[iPosCode+1]*ovsf_code_user1[iPosCode] + Signal[iPosCode+2]*ovsf_code_user1[iPosCode] + Signal[iPosCode+3]*ovsf_code_user1[iPosCode] + Signal[iPosCode+4]*ovsf_code_user1[iPosCode] + Signal[iPosCode+5]*ovsf_code_user1[iPosCode] ;
        }
        pr("Time after RakeReceiver = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);
        _printdecn("Bit ", (int) ( (bit > 0) ? 1 : 0) ) ;
        pr("", 0x10, PR_NEWL);
      }

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


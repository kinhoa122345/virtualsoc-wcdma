#include "../support/simulator/appsupport.h"
#include "../support/simulator/accsupport.h"
#include "hws_support.h"
#include "countersupport.h"
#include "nop_defines.h"
#include "hal.h"
#include "wcdma_signal_fixed.h"
#include "math.h"
#include "qpsk.h"
// #include "fir.h"


int main(int argc, char** arcg)
{
  int num_proc = get_proc_id();
  start_metric();

  register int a, iSymbol, iBuffer, iPosCode ;
  const    int bufferSize = SF/2*SAMPLING_FACTOR;
  register int bit;
  int          Signal[16];
  register int sizeof1int = 1 * sizeof(int);
  register int sizeof2int = 2 * sizeof(int);
  register int sizeof3int = 3 * sizeof(int);
  register int tmp_value ;

  for ( a = 0 ; a < 16 ; a++ )
  {
    Signal[a] = 0 ;
  }

  if (num_proc == 1)
  {
    //Start processing on hw module
    acc_start();
    //Wait for the end of processing on hw module
    acc_wait();

    //For each symbol
    for(iSymbol=0;iSymbol<NB_SYMBOL;iSymbol++)
    {
      //-------------------------------------- FIRST STAGE -----------------------------------------------
      //FIR for I and Q
      pr("Time before FIR-QPSK = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);

      for (iBuffer = 0; iBuffer < bufferSize/2 ;iBuffer+=2)
      {
        Signal[iBuffer] = Signal[iBuffer + bufferSize/2] ;
      }

      for(iBuffer=0; iBuffer < bufferSize; iBuffer++)
      {            
        // Write on the hw FIR I
        acc_write_word(0x0, Signal_I[iBuffer+iSymbol*SF/2*SAMPLING_FACTOR] );

        // Write on the hw FIR Q
        acc_write_word(0x0 + sizeof2int, Signal_Q[iBuffer+iSymbol*SF/2*SAMPLING_FACTOR]);

        // If "" > 6 
        if(iBuffer > 6 && ((iBuffer -7) % 4) == 0)
        {
          register int add = (iBuffer-7)/2;
          Signal[add]     = acc_read_word(sizeof1int) >> 26;
          Signal[add + 1] = acc_read_word(sizeof3int) >> 26;
        }        
      }

      //------------------------------------- SECOND STAGE -----------------------------------------------

        bit = -Signal[0] - 2*Signal[1] - Signal[2] + 2*Signal[7] + Signal[8] - Signal[4] - 2*Signal[5] + Signal[10] + 2*Signal[11] + Signal[12] ;
          
        pr("Time after RakeReceiver = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);
        _printdecn("Bit ", (int) ( (bit > 0) ? 1 : 0) ) ;
        pr("", 0x10, PR_NEWL);
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


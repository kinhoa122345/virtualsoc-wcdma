#include <math.h>

#include <simulator/appsupport.h>
#include <simulator/accsupport.h>
#include <simulator/countersupport.h>
#include <simulator/hws_support.h>

#include "nop_defines.h"
#include "wcdma_signal_fixed.h"
#include "qpsk.h"


#define NULL 0x0

static const int sizeof1int = 1 * sizeof(int);
static const int sizeof2int = 2 * sizeof(int);
static const int sizeof3int = 3 * sizeof(int);
static const int bufferSize = SF/2*SAMPLING_FACTOR;

int  SignalBuffers[2][16] __attribute__ ((section(".LOCAL_SHARED"), unused));
int* inputSignal          __attribute__ ((section(".LOCAL_SHARED"), unused));
int* inputSignalOld       __attribute__ ((section(".LOCAL_SHARED"), unused));

int main(int argc, char** arcg)
{
  int num_proc = get_proc_id();
  start_metric();

  // Init buffer to the first.
  inputSignal    = &SignalBuffers[0][0];
  inputSignalOld = &SignalBuffers[1][0];

  // Init mutex.
  SET_LOCK(0);
  SET_LOCK(1);
  SET_LOCK(2);
  SET_LOCK(3);

  // Start processing on hw module.
  acc_start();
  // Wait for the end of processing on hw module.
  acc_wait();

  switch (num_proc)
  {
    // FIR for I.
    case 1:
    {
      register int  iSymbol      = 0;
      register int  iBuffer      = 0;
      register int* locSignal    = NULL;
      register int* locSignalOld = NULL;

      // For each symbol.
      for(iSymbol = 0; iSymbol < NB_SYMBOL; iSymbol++)
      {
        // Wait mutex0.
        WAIT(0);
        SET_LOCK(0);

        pr("PROCESSOR1: Time before FIR-QPSK = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);

        locSignal    = inputSignal;
        locSignalOld = inputSignalOld;

        pr("PROCESSOR1: Time before SHIFT = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);
        for (iBuffer = 0; iBuffer < bufferSize/2; iBuffer+=2)
          locSignal[iBuffer] = locSignalOld[iBuffer + bufferSize/2];
        pr("PROCESSOR1: Time after SHIFT = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);

        for (iBuffer = 0; iBuffer < bufferSize; iBuffer++)
        {            
          // Write on the hw FIR I.
          acc_write_word(0x0, Signal_I[iBuffer+iSymbol*SF/2*SAMPLING_FACTOR]);
 
          if (iBuffer > 6 && ((iBuffer -7) % 4) == 0)
            locSignal[(iBuffer-7)/2] = acc_read_word(sizeof1int) >> 26;
        }

        pr("PROCESSOR1: Time after FIR-QPSK = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);

        // inputSignal to RakeReceiver.
        //pr("PROCESSOR1: Relase PROCESSOR3 lock at = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);
        SIGNAL(2);
      }

      break;
    }

    // FIR for Q.
    case 2:
    {
      register int  iSymbol      = 0;
      register int  iBuffer      = 0;
      register int* locSignal    = NULL;
      register int* locSignalOld = NULL;

      for(iSymbol = 0; iSymbol < NB_SYMBOL; iSymbol++)
      {
        // Wait mutex1.
        WAIT(1);
        SET_LOCK(1);

        pr("PROCESSOR2: Time before FIR-QPSK = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);

        locSignal    = inputSignal;
        locSignalOld = inputSignalOld;

        for (iBuffer = 0; iBuffer < bufferSize/2; iBuffer+=2)
          locSignal[iBuffer] = locSignalOld[iBuffer + bufferSize/2] ;

        for (iBuffer = 0; iBuffer < bufferSize; iBuffer++)
        {
          // Write on the hw FIR Q
          acc_write_word(sizeof2int, Signal_Q[iBuffer+iSymbol*SF/2*SAMPLING_FACTOR]);

          if (iBuffer > 6 && ((iBuffer -7) % 4) == 0)
          {

            locSignal[(iBuffer-7)/2 + 1] = acc_read_word(sizeof3int) >> 26;
            //_printdecn("PROCESSOR2: Return value: ", locSignal[(iBuffer-7)/2 + 1]);
            //_printdecn("PROCESSOR2: iBuffer: ", iBuffer);
          }
        }

        pr("PROCESSOR2: Time after FIR-QPSK = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);

        // inputSignal to RakeReceiver.
        //pr("PROCESSOR2: Relase PROCESSOR3 lock at = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);
        SIGNAL(3);
      }
      break;
    }

    // Output bit (decoded symbol).
    case 3:
    {
      register int iSymbol = 0;
      register int currentBuffer = 0;
      register int bit = 0;

      // Init SignalBuffers.
      {
        int  a = 0;
        int  b = 0;
        for (a = 0; a < 2; ++a)
          for (b = 0; b < 16 ; b++)
            { SignalBuffers[a][b] = 0 ; }

        SIGNAL(0);
        SIGNAL(1);
      }

      for (iSymbol = 0; iSymbol < NB_SYMBOL; iSymbol++)
      {
        // Wait results of FIR1 and FIR2.
        //pr("PROCESSOR3: Time at wait for results = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);

        WAIT(2);
        SET_LOCK(2);
        //pr("PROCESSOR3: First lock passed at = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);
        WAIT(3);
        SET_LOCK(3);
        //pr("PROCESSOR3: Second lock passed at = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);

        pr("PROCESSOR3: Time before RakeReceiver = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);

        // Register the current buffer to process.
        inputSignalOld = inputSignal;

        // Switch buffers.
        currentBuffer++;
        currentBuffer %= 2;
        inputSignal = &SignalBuffers[currentBuffer][0];

        // Relaunch FIR1 and FIR2.
        SIGNAL(0);
        SIGNAL(1);

        // Process data.
        bit =
          -inputSignalOld[0] - 2*inputSignalOld[1] - inputSignalOld[2]  + 2*inputSignalOld[7]  + inputSignalOld[8] -
           inputSignalOld[4] - 2*inputSignalOld[5] + inputSignalOld[10] + 2*inputSignalOld[11] + inputSignalOld[12];
          
        pr("PROCESSOR3: Time after RakeReceiver = ", 0x10, PR_STRING | PR_TSTAMP | PR_NEWL);
        _printdecn("Bit: ", (int) ( (bit > 0) ? 1 : 0) );
        pr("", 0x10, PR_NEWL);
      }
      break;
    }

    default:
    {
      _printstrn("Only 3 processors are needed!");
      break;
    }
  }

  stop_metric();
  //Stop metrics
  _printstrn("Done");
  //Check results

  //End
  return(0);
}


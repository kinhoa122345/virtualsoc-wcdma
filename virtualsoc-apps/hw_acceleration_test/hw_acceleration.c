//HAL
#include "appsupport.h"
#include "accsupport.h"
#include "nop_defines.h"

//HAL: Malloc (shmalloc)
#include "hal.h"
//#include "gomp/libgomp.h"
//#include "libgomp_globals.c"
//#include "hal-root.c"
//#include "memutils.c"

//HW accelerations
#include "hws_support.h"
#include "countersupport.h"


int main()
{
  //Get num proc
  int num_proc = get_proc_id();
  _printdecn("num proc=",num_proc);

  if (num_proc==1)
  {
    //################ HW MODULE TEST #################
    _printstrp("Test hw acceleration!");

    start_metric();

    //Start processing on hw module
    acc_start();

    //Wait for the end of processing on hw module
    acc_wait();

    int i;
    for(i = 0; i < 10; i++)
    {
      // Write on the hw FIR1
      acc_write_word(0x0, i);

      // Write on the hw FIR2
      acc_write_word(0x0 + 2*sizeof(int), i+3);

      // Wait for the end of processing on hw module
      acc_wait();

      // Read on the hw FIR1.
      uint32_t tmp_value = acc_read_word(0x0 + sizeof(int));
      int value = *((int*)(&tmp_value));
      _printdecp("FIR1 value is: ", value);

      // Read on the hw FIR2.
      tmp_value = acc_read_word(0x0 + 3*sizeof(int));
      value = *((int*)(&tmp_value));
      _printdecp("FIR2 value is: ", value);
    }

    stop_metric();

    //################ COUNTER TEST #################
    _printstrp("Test counter!");

    counter_init();
    _1000_nop_block;
    counter_get();
  }
  else
  {
    _printstrn("Only 1 processor is supported!");
  }

  return 0;
}


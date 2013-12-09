//HAL
#include "appsupport.h"
#include "accsupport.h"
#include "nop_defines.h"

//HAL: Malloc (shmalloc)
#include "gomp/hal.h"
//#include "gomp/libgomp.h"
//#include "libgomp_globals.c"
//#include "hal-root.c"
//#include "memutils.c"

//HW accelerations
#include "hws_support.h"
#include "countersupport.h"


int main()
{
	start_metric();

	//Get num proc
	int num_proc = get_proc_id();
	_printdecn("num proc=",num_proc);
 
	if(num_proc==1)
	{
		//################ HW MODULE TEST #################
		_printstrp("Test hw acceleration!");

		//Write on the hw module
		int i;
		for(i=0;i<10;i++) acc_write_word(0x4, 0x25);

		//Start processing on hw module
	  	acc_start();

		//Wait for the end of processing on hw module
		acc_wait();

		//Read on the hw module
		_printhexp("Content at the address 0x4 is ", acc_read_word(0x4) );


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

	stop_metric();

	return 0;
}


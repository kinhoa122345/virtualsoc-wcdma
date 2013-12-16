#include <virtualsoc/cluster/cl_acc.h>


#define INPUT1_ADDR  ACCELERATOR_MEM_ADDR + 0*sizeof(int)
#define OUTPUT1_ADDR ACCELERATOR_MEM_ADDR + 1*sizeof(int)
#define INPUT2_ADDR  ACCELERATOR_MEM_ADDR + 2*sizeof(int)
#define OUTPUT2_ADDR ACCELERATOR_MEM_ADDR + 3*sizeof(int)

// Get_word_size
uint32_t cl_acc::get_word_size(uint32_t bw)
{
  uint32_t size;

  // Word, half word or byte?
  switch (bw)
  {
    case 0 : size = 0x4; break;
    case 1 : size = 0x1; break;
    case 2 : size = 0x2; break;
    default :
      std::cout
          << "Invalid word size"
          << std::endl;
      exit(1);
  }

  return size;
}

// Execute
void cl_acc::execute(void)
{
  // Local variables
  PINOUT   tmp_pinout;
  uint32_t addr;
  uint32_t burst;
  uint32_t data;
  uint32_t bw;
  bool     wr;
  uint32_t size;

  // Initializations
  sl_rdy.write(false);

  // Main thread
  while(true)
  {
    // Wait for request
    if (!sl_req.read()) wait(sl_req.posedge_event());

    // Get request
    tmp_pinout = slave_port.read();
    addr       = tmp_pinout.address; // Address
    burst      = tmp_pinout.burst;   // Size of burst
    bw         = tmp_pinout.bw;      // Size of data
    wr         = tmp_pinout.rw;      // Read/write cmd
    size       = get_word_size(bw);

    /*std::cout
        << "ACCELERATOR Execute function call."
        << std::endl;*/

    // If not started and not queried to start, then continue.
    if (status == CL_ACC_STOP &&
        addr != ACCELERATOR_START_ADDR &&
        addr != ACCELERATOR_READY_ADDR)
    {
      // Handshaking
      sl_rdy.write(true);
      wait();
      sl_rdy.write(false);
      wait();

      //std::cout << "ACCELERATOR Idle." << std::endl;

      continue;
    }

    // It is a READ request
    if (!wr)
    {
      //std::cout << "ACCELERATOR: Read " << std::hex << addr - ACCELERATOR_START_ADDR << std::dec << std::endl;
      if (addr == ACCELERATOR_READY_ADDR)
      {
        // Debug
        /*std::cout
            << "ACCELERATOR Wait for the end of the processing at "
            << sc_time_stamp()
            << std::endl;*/

        // Wait the end of the processing
        if (status == CL_ACC_INACTIVE || status == CL_ACC_START)
          tmp_pinout.data = 1;
        else
          tmp_pinout.data = 0;

        /*std::cout << "ACCELERATOR: Is active: " << tmp_pinout.data << std::endl;
        std::cout << "ACCELERATOR: Status: " << status << std::endl;*/

        // End of processing
        //tmp_pinout.data = 1;

        // Write answer
        slave_port.write(tmp_pinout);

        // Handshaking
        sl_rdy.write(true);
        wait();
        sl_rdy.write(false);
        wait();
      }
      else
      {
        // Change status
        status = CL_ACC_READ;

        // Debug
        /*std::cout
            << "ACCELERATOR Read at the address "
            << std::hex
            << addr
            << " at "
            << sc_time_stamp()
            << std::endl;*/

        // Return the requested data
        for (int i = 0; i < burst; i ++)
        {
          wait();
          sl_rdy.write(false);
          data = this->Read(addr, bw);

          // Wait 1 cycle between burst beat
          wait();

          // Increment the address for the next beat
          addr += size;

          tmp_pinout.data = data;
          slave_port.write(tmp_pinout);
          sl_rdy.write(true);
        }

        wait();
        sl_rdy.write(false);
        wait();

        // Change status
        status = CL_ACC_INACTIVE;
      }
    }
    // It is a WRITE request
    else
    {
      // Get the data to write
      data = tmp_pinout.data;

      // Control part
      if (addr == ACCELERATOR_START_ADDR)
      {
        //std::cout << "ACCELERATOR: Start status: " << data << std::endl;
        if (data == 1)
        {
          status = CL_ACC_START;

          // Send active signal
          start_processing.notify();

          // Debug
          /*std::cout
              << "ACCELERATOR: Start processing"
              << std::endl;*/
        }
        else
        {
          status = CL_ACC_INACTIVE;

          // Debug
          /*std::cout
              << "ACCELERATOR: Stop processing"
              << std::endl;*/
        }

        // Handshaking
        sl_rdy.write(true);
        wait();
        sl_rdy.write(false);
        wait();
      }
      else
      {
        // Change status
        status = CL_ACC_WRITE;

        // Debug
        /*std::cout
            << "ACCELERATOR Write at the address "
            << hex << addr
            << " the value "
            << data
            << " at "
            << sc_time_stamp()
            << std::endl;*/

        uint32_t cur_addr = addr;

        // Write the data in the request
        for (int i = 0; i < burst; i ++)
        {
          wait();
          sl_rdy.write(false);
          Write(addr, data, bw);

          // Wait 1 cycle between burst beat
          wait();

          // Increment the address for the next beat
          addr += size;
          sl_rdy.write(true);
        }

        switch (cur_addr)
        {
          case INPUT1_ADDR:
            start_processing_fir1.notify();
            //std::cout << "ACCELERATOR: FIR1 pushed." << std::endl;
            break;
          case INPUT2_ADDR:
            start_processing_fir2.notify();
            break;
          default:
            std::cout << "ACCELERATOR: Bad address pushed: " << std::hex << addr << std::dec << std::endl;
            break;
        }

        wait();
        sl_rdy.write(false);
        wait();

        // Change status
        status = CL_ACC_INACTIVE;
      }
    }
  }
}

void cl_acc::acc_processing_fir1(void)
{
  //Debug
  /*std::cout
      << "ACCELERATOR: FIR1 START!"
      << std::endl;*/

  while (true)
  {
    // Wait for an input.
    wait(start_processing_fir1);

    /*std::cout
        << "ACCELERATOR: Processing FIR1 request."
        << std::endl;*/

    uint32_t const& input = Read(INPUT1_ADDR, MEM_WORD);

    // Send value to FIR.
    /*std::cout
        << "ACCELERATOR: FIR1 input: "
        << reinterpret_cast<int const&>(input)
        << std::endl;*/

    fir_module_1.io.x.write(reinterpret_cast<int const&>(input));

    // Wait for high clock.
    // Because the pipeline need one tick to compute the pipelined result.
    // This will put a latency between input and output.
    wait();

    // Get FIR(t-6) result.
    int const& output = fir_module_1.io.y.read();
    Write(OUTPUT1_ADDR, reinterpret_cast<uint32_t const&>(output),MEM_WORD);

    // Return in inactive mode.
    status = CL_ACC_INACTIVE;

    /*std::cout
        << "ACCELERATOR: Finish to write input in FIR1."
        << std::endl;*/
  }

  // Debug
  //cout << "ACCELERATOR: FIR1 DONE!"<<endl;
}

void cl_acc::acc_processing_fir2(void)
{
  // Debug
  /*std::cout
      << "ACCELERATOR: FIR2 START!"
      << std::endl;*/

  while (true)
  {
    // Wait for an input.
    wait(start_processing_fir2);

    /*std::cout
        << "ACCELERATOR: Processing FIR2 request."
        << std::endl;*/

    uint32_t const& input = Read(INPUT2_ADDR, MEM_WORD);

    // Send value to FIR.
    /*std::cout
        << "ACCELERATOR: FIR2 input: "
        << reinterpret_cast<int const&>(input)
        << std::endl;*/

    fir_module_2.io.x.write(reinterpret_cast<int const&>(input));

    // Wait for high clock.
    // Because the pipeline need one tick to compute the pipelined result.
    // This will put a latency between input and output.
    wait();

    // Get FIR(t-6) result.
    int const& output = fir_module_2.io.y.read();
    Write(OUTPUT2_ADDR, reinterpret_cast<uint32_t const&>(output),MEM_WORD);

    // Return in inactive mode.
    status = CL_ACC_INACTIVE;

    /*std::cout
        << "ACCELERATOR: Finish to write input in FIR2."
        << std::endl;*/
  }

  //Debug
  //cout << "ACCELERATOR: FIR2 DONE!"<<endl;
}


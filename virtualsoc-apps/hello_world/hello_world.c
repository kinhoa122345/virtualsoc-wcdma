#include <simulator/appsupport.h>
#include <simulator/countersupport.h>

int main()
{
  start_metric();
  //counter_init();
  _printstrp("Hello World!");
  //counter_get();
  stop_metric();
  return 0;
}

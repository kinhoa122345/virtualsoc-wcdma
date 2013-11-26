
#include <gomp/gomp_config.h>
#include <gomp/bar.h>

/* Application-level barrier */

void
GOMP_barrier()
{
  gomp_hal_barrier(_ms_barrier);
}

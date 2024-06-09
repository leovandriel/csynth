#include "../../src/util/time.h"
#include "./test.h"

#include <math.h>

void test_time()
{
    time_t tme = time(NULL);
    double time1 = time_wall();
    assert(fabs(tme - time1) < 1);
    double time2 = time_wall();
    assert(time2 - time1 < 0.001);
}

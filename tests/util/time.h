#include "../../src/util/time.h"
#include "./test.h"

#include <math.h>

void test_time()
{
    time_t t = time(NULL);
    double t1 = time_wall();
    assert(fabs(t - t1) < 1);
    double t2 = time_wall();
    assert(t2 - t1 < 0.001);
}

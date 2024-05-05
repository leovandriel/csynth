#include "../../../src/func/gen/noise.h"
#include "../../util/test.h"

void test_noise()
{
    for (int i = 0; i < 100; i++)
    {
        assert_gen_range(gen_create(noise(), .1), -1.0, 1.0);
    }
}

#include "../../../src/func/gen/gauss.h"
#include "../../util/test.h"

void test_gauss()
{
    for (int i = 0; i < 100; i++)
    {
        assert_gen_range(gen_create(gauss(), .1), -4.0, 4.0);
    }
}

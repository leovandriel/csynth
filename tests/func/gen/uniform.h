#include "../../../src/func/gen/uniform.h"
#include "../../util/test.h"

void test_uniform()
{
    for (int i = 0; i < 100; i++)
    {
        assert_gen_range(gen_create(uniform(), .1), -1.0, 1.0);
    }
}

#include "../../../src/func/gen/gauss.h"
#include "../../util/test.h"

void test_gauss()
{
    for (int i = 0; i < 100; i++)
    {
        Gen *gen = gen_create(gauss(), .1);
        assert_gen_range(gen, -4.0, 4.0);
        gen_free(gen);
    }
    func_free();
}

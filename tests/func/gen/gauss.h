#include "../../../src/func/gen/gauss.h"
#include "../../util/test.h"

void test_gauss()
{
    for (int i = 0; i < 100; i++)
    {
        Gen *gen = gen_create(gauss());
        Eval eval = {.delta = 0.1};
        assert_double_range(gen_eval(gen, eval), -4.0, 4.0);
        gen_free(gen);
    }
    func_free();
}

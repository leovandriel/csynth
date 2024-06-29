#include "../../../src/func/gen/uniform.h"
#include "../../util/test.h"

void test_uniform()
{
    for (int i = 0; i < 100; i++)
    {
        Gen *gen = gen_create(uniform());
        Eval eval = eval_create(0.1);
        assert_double_range(gen_eval(gen, eval), -1.0, 1.0);
        gen_free(gen);
    }
    func_free();
}

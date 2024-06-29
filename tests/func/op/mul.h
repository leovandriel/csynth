#include "../../../src/func/op/mul.h"
#include "../../util/test.h"

void test_mul()
{
    Gen *gen1 = gen_create(mul(const_(1), const_(1)));
    Gen *gen2 = gen_create(mul(const_(1), const_(2), const_(3)));
    Gen *gen3 = gen_create(mul(const_(1)));
    Eval eval = {.step = {0.1, 0.1}};
    assert_double_equal(gen_eval(gen1, eval), 1.0);
    assert_double_equal(gen_eval(gen2, eval), 6.0);
    assert_double_equal(gen_eval(gen3, eval), 1.0);
    gen_free(gen1);
    gen_free(gen2);
    gen_free(gen3);
    func_free();
}

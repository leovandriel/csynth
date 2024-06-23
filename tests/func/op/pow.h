#include "../../../src/func/op/pow.h"
#include "../../util/test.h"

void test_pow()
{
    Gen *gen1 = gen_create(pow_op(const_(1), const_(1)));
    Gen *gen2 = gen_create(pow_op(const_(1), const_(2)));
    Gen *gen3 = gen_create(pow_op(const_(2), const_(1)));
    Gen *gen4 = gen_create(pow_op(const_(2), const_(2)));
    Eval eval = {.delta = 0.1};
    assert_double_equal(gen_eval(gen1, eval), 1.0);
    assert_double_equal(gen_eval(gen2, eval), 1.0);
    assert_double_equal(gen_eval(gen3, eval), 2.0);
    assert_double_equal(gen_eval(gen4, eval), 4.0);
    gen_free(gen1);
    gen_free(gen2);
    gen_free(gen3);
    gen_free(gen4);
    func_free();
}

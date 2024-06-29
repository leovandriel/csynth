#include "../../../src/func/op/sin.h"
#include "../../util/test.h"

void test_sin()
{
    Gen *gen1 = gen_create(sin_op(const_(0)));
    Gen *gen2 = gen_create(sin_op(const_(1)));
    Gen *gen3 = gen_create(sin_op(const_(2)));
    Eval eval = {.step = {0.1, 0.1}};
    assert_double_equal(gen_eval(gen1, eval), 0.0);
    assert_double_equal(gen_eval(gen2, eval), 0.8414709848078965);
    assert_double_equal(gen_eval(gen3, eval), 0.9092974268256817);
    gen_free(gen1);
    gen_free(gen2);
    gen_free(gen3);
    func_free();
}

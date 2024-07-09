#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/sum.h"
#include "../../util/test.h"

void test_sum()
{
    Gen *gen = gen_create(sum_create(const_(0.1)));
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.1);
    assert_double_equal(gen_eval(gen, &eval), 0.2);
    assert_double_equal(gen_eval(gen, &eval), 0.3);
    assert_double_equal(gen_eval(gen, &eval), 0.4);
    gen_free(gen);
    func_free();
}

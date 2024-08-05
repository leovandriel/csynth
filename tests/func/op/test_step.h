#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/step.h"
#include "../../../src/func/op/sum.h"
#include "../../util/test.h"

void test_step(void)
{
    Gen *gen = gen_create(step_create(const_create(0.5), sum_create(const_create(0.1))));
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    gen_free(gen);
    func_free();
}

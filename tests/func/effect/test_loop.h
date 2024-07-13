#include "../../../src/func/effect/loop.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/step.h"
#include "../../../src/func/op/sum.h"
#include "../../util/test.h"

void test_loop()
{
    Gen *gen = gen_create(loop_create(const_(0.2), step_create(const_(0.3), sum_create(const_(0.1)))));
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    gen_free(gen);
    func_free();
}

#include "../../../src/func/gen/timer.h"
#include "../../../src/func/op/step.h"
#include "../../util/test.h"

void test_step()
{
    Func *time = step_op(timer(), const_(0.5));
    Gen *gen = gen_create(time, 0.1);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 1.0);
    assert_gen_equal(gen, 1.0);
    assert_gen_equal(gen, 1.0);
    assert_gen_equal(gen, 1.0);
    assert_gen_equal(gen, 1.0);
    assert_gen_equal(gen, 1.0);
}

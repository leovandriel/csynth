#include "../../../src/func/gen/timer.h"
#include "../../../src/func/op/smooth.h"
#include "../../util/test.h"

void test_smooth()
{
    Func *t = smooth_op(timer(), const_(0.3), const_(0.7));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.000000);
    assert_gen_equal(g, 0.000000);
    assert_gen_equal(g, 0.000000);
    assert_gen_equal(g, 0.000000);
    assert_gen_equal(g, 0.156250);
    assert_gen_equal(g, 0.500000);
    assert_gen_equal(g, 0.843750);
    assert_gen_equal(g, 1.000000);
    assert_gen_equal(g, 1.000000);
    assert_gen_equal(g, 1.000000);
}
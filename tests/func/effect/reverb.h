#include "../../../src/func/effect/reverb.h"
#include "../../util/test.h"

void test_reverb()
{
    Func *t = reverb(const_(1), const_(.2), const_(.5));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.00000);
    assert_gen_equal(g, 0.00000);
    assert_gen_equal(g, 1.00000);
    assert_gen_equal(g, 1.00000);
    assert_gen_equal(g, 1.50000);
    assert_gen_equal(g, 1.50000);
    assert_gen_equal(g, 1.75000);
    assert_gen_equal(g, 1.75000);
    assert_gen_equal(g, 1.87500);
    assert_gen_equal(g, 1.87500);
    assert_gen_equal(g, 1.93750);
    assert_gen_equal(g, 1.93750);
}

#include "../../../src/func/effect/delay.h"
#include "../../util/test.h"

void test_delay()
{
    Func *t = delay(const_(1), const_(0.5));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
}

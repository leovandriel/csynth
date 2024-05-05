#include "../../../src/func/envelope/adsr.h"
#include "../../util/test.h"

void test_adsr()
{
    Func *t = adsr_(0.01, 0.1, 0.7, 0.2, 1.2);
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.000);
    assert_gen_equal(g, 0.730);
    assert_gen_equal(g, 0.700);
    assert_gen_equal(g, 0.700);
    assert_gen_equal(g, 0.700);
    assert_gen_equal(g, 0.700);
    assert_gen_equal(g, 0.700);
    assert_gen_equal(g, 0.700);
    assert_gen_equal(g, 0.700);
    assert_gen_equal(g, 0.700);
    assert_gen_equal(g, 0.700);
    assert_gen_equal(g, 0.350);
    assert_gen_equal(g, 0.000);
    assert_gen_equal(g, 0.000);
    assert_gen_equal(g, 0.000);
}

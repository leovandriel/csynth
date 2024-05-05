#include "../../../src/func/filter/limit.h"
#include "../../../src/func/gen/square.h"
#include "../../util/test.h"

void test_limit()
{
    Func *t = limit(square(const_(1)), const_(3));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.30);
    assert_gen_equal(g, 0.60);
    assert_gen_equal(g, 0.90);
    assert_gen_equal(g, 1.00);
    assert_gen_equal(g, 1.00);
    assert_gen_equal(g, 0.70);
    assert_gen_equal(g, 0.40);
    assert_gen_equal(g, 0.10);
    assert_gen_equal(g, -0.20);
    assert_gen_equal(g, -0.50);
    assert_gen_equal(g, -0.20);
    assert_gen_equal(g, 0.10);
}

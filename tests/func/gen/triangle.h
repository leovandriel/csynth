#include "../../../src/func/gen/triangle.h"
#include "../../util/test.h"

void test_triangle()
{
    Func *t = triangle(const_(1));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.4);
    assert_gen_equal(g, 0.8);
    assert_gen_equal(g, 0.8);
    assert_gen_equal(g, 0.4);
    assert_gen_equal(g, -0.0);
    assert_gen_equal(g, -0.4);
    assert_gen_equal(g, -0.8);
    assert_gen_equal(g, -0.8);
    assert_gen_equal(g, -0.4);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.4);
}

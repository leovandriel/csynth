#include "../../../src/func/gen/square.h"
#include "../../util/test.h"

void test_square()
{
    Func *t = square(const_(1));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, -1.0);
    assert_gen_equal(g, -1.0);
    assert_gen_equal(g, -1.0);
    assert_gen_equal(g, -1.0);
    assert_gen_equal(g, -1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
}

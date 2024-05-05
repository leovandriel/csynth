#include "../../../src/func/gen/saw.h"
#include "../../util/test.h"

void test_saw()
{
    Func *t = saw(const_(1));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.2);
    assert_gen_equal(g, 0.4);
    assert_gen_equal(g, 0.6);
    assert_gen_equal(g, 0.8);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, -0.8);
    assert_gen_equal(g, -0.6);
    assert_gen_equal(g, -0.4);
    assert_gen_equal(g, -0.2);
    assert_gen_equal(g, -0.0);
}

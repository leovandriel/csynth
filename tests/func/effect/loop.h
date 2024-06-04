#include "../../../src/func/effect/loop.h"
#include "../../../src/func/envelope/step.h"
#include "../../util/test.h"

void test_loop()
{
    Func *t = loop(step_env(const_(0.3)), const_(0.5));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
}

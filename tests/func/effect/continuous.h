#include "../../../src/func/effect/continuous.h"
#include "../../../src/func/effect/loop.h"
#include "../../../src/func/env/envs.h"
#include "../../util/test.h"

void test_continuous()
{
    Func *t = loop_(continuous(linear_(0, 1, 1)), 2);
    Gen *g = gen_create(t, 1);
    assert_gen_equal(g, 0);
    assert_gen_equal(g, 1);
    assert_gen_equal(g, 2);
    assert_gen_equal(g, 3);
    assert_gen_equal(g, 4);
}

#include "../../../src/func/effect/continuous.h"
#include "../../../src/func/effect/loop.h"
#include "../../../src/func/filter/envelopes.h"
#include "../../util/test.h"

void test_continuous()
{
    Func *time = loop_(continuous(linear_env_(0, 1, 1)), 2);
    Gen *gen = gen_create(time, 1);
    assert_gen_equal(gen, 0);
    assert_gen_equal(gen, 1);
    assert_gen_equal(gen, 2);
    assert_gen_equal(gen, 3);
    assert_gen_equal(gen, 4);
}

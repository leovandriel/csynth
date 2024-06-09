#include "../../../src/func/effect/reverb.h"
#include "../../util/test.h"

void test_reverb()
{
    Func *time = reverb(const_(1), const_(.2), const_(.5));
    Gen *gen = gen_create(time, 0.1);
    assert_gen_equal(gen, 0.00000);
    assert_gen_equal(gen, 0.00000);
    assert_gen_equal(gen, 1.00000);
    assert_gen_equal(gen, 1.00000);
    assert_gen_equal(gen, 1.50000);
    assert_gen_equal(gen, 1.50000);
    assert_gen_equal(gen, 1.75000);
    assert_gen_equal(gen, 1.75000);
    assert_gen_equal(gen, 1.87500);
    assert_gen_equal(gen, 1.87500);
    assert_gen_equal(gen, 1.93750);
    assert_gen_equal(gen, 1.93750);
}

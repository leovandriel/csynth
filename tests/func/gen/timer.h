#include "../../../src/func/gen/timer.h"
#include "../../util/test.h"

void test_timer()
{
    Func *time = timer();
    Gen *gen = gen_create(time, 0.1);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.1);
    assert_gen_equal(gen, 0.2);
    assert_gen_equal(gen, 0.3);
    assert_gen_equal(gen, 0.4);
}

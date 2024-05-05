#include "../../../src/func/gen/timer.h"
#include "../../util/test.h"

void test_timer()
{
    Func *t = timer();
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.1);
    assert_gen_equal(g, 0.2);
    assert_gen_equal(g, 0.3);
    assert_gen_equal(g, 0.4);
}

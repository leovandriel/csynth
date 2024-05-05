#include "../../../src/func/filter/chorus.h"
#include "../../../src/func/gen/sine.h"
#include "../../util/test.h"

void test_chorus()
{
    Func *t = chorus_(sine_(10), sine_(.2), 0.2, 0.2);
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
}

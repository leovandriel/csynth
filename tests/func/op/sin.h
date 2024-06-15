#include "../../../src/func/op/sin.h"
#include "../../util/test.h"

void test_sin()
{
    Gen *g1 = gen_create(sin_op(const_(0)), .1);
    Gen *g2 = gen_create(sin_op(const_(1)), .1);
    Gen *g3 = gen_create(sin_op(const_(2)), .1);
    assert_gen_equal(g1, 0.0);
    assert_gen_equal(g2, 0.8414709848078965);
    assert_gen_equal(g3, 0.9092974268256817);
    gen_free(g1);
    gen_free(g2);
    gen_free(g3);
    func_free();
}

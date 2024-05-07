#include "../../../src/func/op/sin.h"
#include "../../util/test.h"

void test_sin()
{
    assert_gen_equal(gen_create(sin_op(const_(0)), .1), 0.0);
    assert_gen_equal(gen_create(sin_op(const_(1)), .1), 0.8414709848078965);
    assert_gen_equal(gen_create(sin_op(const_(2)), .1), 0.9092974268256817);
}

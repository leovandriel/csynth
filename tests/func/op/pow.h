#include "../../../src/func/op/pow.h"
#include "../../util/test.h"

void test_pow()
{
    assert_gen_equal(gen_create(pow_op(const_(1), const_(1)), .1), 1.0);
    assert_gen_equal(gen_create(pow_op(const_(1), const_(2)), .1), 1.0);
    assert_gen_equal(gen_create(pow_op(const_(2), const_(1)), .1), 2.0);
    assert_gen_equal(gen_create(pow_op(const_(2), const_(2)), .1), 4.0);
}

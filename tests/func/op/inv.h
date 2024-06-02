#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/inv.h"
#include "../../util/test.h"

void test_inv()
{
    assert_gen_equal(gen_create(inv(const_(1)), .1), 1.0);
    assert_gen_equal(gen_create(inv(const_(-2)), .1), -0.5);
}

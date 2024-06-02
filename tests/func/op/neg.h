#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/neg.h"
#include "../../util/test.h"

void test_neg()
{
    assert_gen_equal(gen_create(neg(const_(1)), .1), -1.0);
    assert_gen_equal(gen_create(neg(const_(-2)), .1), 2.0);
}

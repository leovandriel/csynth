#include "../../../src/func/gen/const.h"
#include "../../util/test.h"

void test_const()
{
    assert_gen_equal(gen_create(const_(1), .1), 1.0);
    assert_gen_equal(gen_create(const_(-2), .1), -2.0);
}

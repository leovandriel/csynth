#include "../../../src/func/op/mul.h"
#include "../../util/test.h"

void test_mul()
{
    assert_gen_equal(gen_create(mul(const_(1), const_(1)), .1), 1.0);
    assert_gen_equal(gen_create(mul(const_(1), const_(2), const_(3)), .1), 6.0);
    assert_gen_equal(gen_create(mul(const_(1)), .1), 1.0);
}

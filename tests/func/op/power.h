#include "../../../src/func/op/power.h"
#include "../../util/test.h"

void test_power()
{
    assert_gen_equal(gen_create(power(const_(1), const_(1)), .1), 1.0);
    assert_gen_equal(gen_create(power(const_(1), const_(2)), .1), 1.0);
    assert_gen_equal(gen_create(power(const_(2), const_(1)), .1), 2.0);
    assert_gen_equal(gen_create(power(const_(2), const_(2)), .1), 4.0);
}

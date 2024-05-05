#include "../../../src/func/op/max.h"
#include "../../util/test.h"

void test_max()
{
    assert_gen_equal(gen_create(max(const_(1), const_(2)), .1), 2.0);
    assert_gen_equal(gen_create(max(const_(2), const_(1)), .1), 2.0);
    assert_gen_equal(gen_create(max(const_(4), const_(2), const_(3)), .1), 4.0);
    assert_gen_equal(gen_create(max(const_(1)), .1), 1.0);
}

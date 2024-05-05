#include "../../../src/func/op/min.h"
#include "../../util/test.h"

void test_min()
{
    assert_gen_equal(gen_create(min(const_(1), const_(2)), .1), 1.0);
    assert_gen_equal(gen_create(min(const_(2), const_(1)), .1), 1.0);
    assert_gen_equal(gen_create(min(const_(4), const_(2), const_(3)), .1), 2.0);
    assert_gen_equal(gen_create(min(const_(1)), .1), 1.0);
}

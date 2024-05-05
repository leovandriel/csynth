#include "../../../src/func/op/add.h"
#include "../../util/test.h"

void test_add()
{
    assert_gen_equal(gen_create(add(const_(1), const_(1)), .1), 2.0);
    assert_gen_equal(gen_create(add(const_(1), const_(2), const_(3)), .1), 6.0);
    assert_gen_equal(gen_create(add(const_(1)), .1), 1.0);
}

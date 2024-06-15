#include "../../../src/func/op/add.h"
#include "../../util/test.h"

void test_add()
{
    Gen *g1 = gen_create(add(const_(1), const_(1)), .1);
    Gen *g2 = gen_create(add(const_(1), const_(2), const_(3)), .1);
    Gen *g3 = gen_create(add(const_(1)), .1);
    assert_gen_equal(g1, 2.0);
    assert_gen_equal(g2, 6.0);
    assert_gen_equal(g3, 1.0);
    gen_free(g1);
    gen_free(g2);
    gen_free(g3);
    func_free();
}

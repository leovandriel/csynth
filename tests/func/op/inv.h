#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/inv.h"
#include "../../util/test.h"

void test_inv()
{
    Gen *g1 = gen_create(inv(const_(1)), .1);
    Gen *g2 = gen_create(inv(const_(-2)), .1);
    assert_gen_equal(g1, 1.0);
    assert_gen_equal(g2, -0.5);
    gen_free(g1);
    gen_free(g2);
    func_free();
}

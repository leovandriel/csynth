#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/neg.h"
#include "../../util/test.h"

void test_neg()
{
    Gen *g1 = gen_create(neg(const_(1)), .1);
    Gen *g2 = gen_create(neg(const_(-2)), .1);
    assert_gen_equal(g1, -1.0);
    assert_gen_equal(g2, 2.0);
    gen_free(g1);
    gen_free(g2);
    func_free();
}

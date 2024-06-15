#include "../../../src/func/op/pow.h"
#include "../../util/test.h"

void test_pow()
{
    Gen *g1 = gen_create(pow_op(const_(1), const_(1)), .1);
    Gen *g2 = gen_create(pow_op(const_(1), const_(2)), .1);
    Gen *g3 = gen_create(pow_op(const_(2), const_(1)), .1);
    Gen *g4 = gen_create(pow_op(const_(2), const_(2)), .1);
    assert_gen_equal(g1, 1.0);
    assert_gen_equal(g2, 1.0);
    assert_gen_equal(g3, 2.0);
    assert_gen_equal(g4, 4.0);
    gen_free(g1);
    gen_free(g2);
    gen_free(g3);
    gen_free(g4);
    func_free();
}

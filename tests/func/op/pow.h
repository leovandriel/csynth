#include "../../../src/func/op/pow.h"
#include "../../util/test.h"

void test_pow()
{
    Gen *gen1 = gen_create(pow_op(const_(1), const_(1)), .1);
    Gen *gen2 = gen_create(pow_op(const_(1), const_(2)), .1);
    Gen *gen3 = gen_create(pow_op(const_(2), const_(1)), .1);
    Gen *gen4 = gen_create(pow_op(const_(2), const_(2)), .1);
    assert_gen_equal(gen1, 1.0);
    assert_gen_equal(gen2, 1.0);
    assert_gen_equal(gen3, 2.0);
    assert_gen_equal(gen4, 4.0);
    gen_free(gen1);
    gen_free(gen2);
    gen_free(gen3);
    gen_free(gen4);
    func_free();
}

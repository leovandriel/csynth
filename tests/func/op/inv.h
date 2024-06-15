#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/inv.h"
#include "../../util/test.h"

void test_inv()
{
    Gen *gen1 = gen_create(inv(const_(1)), .1);
    Gen *gen2 = gen_create(inv(const_(-2)), .1);
    assert_gen_equal(gen1, 1.0);
    assert_gen_equal(gen2, -0.5);
    gen_free(gen1);
    gen_free(gen2);
    func_free();
}

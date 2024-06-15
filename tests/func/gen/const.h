#include "../../../src/func/gen/const.h"
#include "../../util/test.h"

void test_const()
{
    Gen *gen1 = gen_create(const_(1), .1);
    Gen *gen2 = gen_create(const_(-2), .1);
    assert_gen_equal(gen1, 1.0);
    assert_gen_equal(gen2, -2.0);
    gen_free(gen1);
    gen_free(gen2);
    func_free();
}

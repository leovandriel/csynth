#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/inv.h"
#include "../../../src/func/op/ops.h"
#include "../../util/test.h"

void test_inv()
{
    Gen *gen1 = gen_create(inv(const_(1)));
    Gen *gen2 = gen_create(inv(const_(-2)));
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen1, &eval), 1.0);
    assert_double_equal(gen_eval(gen2, &eval), -0.5);
    gen_free(gen1);
    gen_free(gen2);
    func_free();
}

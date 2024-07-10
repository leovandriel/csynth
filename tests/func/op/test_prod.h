#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/prod.h"
#include "../../util/test.h"

void test_prod()
{
    Gen *gen = gen_create(prod_create(const_(1.1)));
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), 1.0000000000000000);
    assert_double_equal(gen_eval(gen, &eval), 1.1000000000000001);
    assert_double_equal(gen_eval(gen, &eval), 1.2100000000000002);
    assert_double_equal(gen_eval(gen, &eval), 1.3310000000000004);
    assert_double_equal(gen_eval(gen, &eval), 1.4641000000000006);
    assert_double_equal(gen_eval(gen, &eval), 1.6105100000000008);
    gen_free(gen);
    func_free();
}

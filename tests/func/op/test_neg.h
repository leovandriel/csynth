#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/neg.h"
#include "../../util/test.h"

void test_neg(void)
{
    Gen *gen1 = gen_create(neg_create(const_create(1)));
    Gen *gen2 = gen_create(neg_create(const_create(-2)));
    assert_double_equal(gen_eval(gen1, NULL), -1.0);
    assert_double_equal(gen_eval(gen2, NULL), 2.0);
    gen_free(gen1);
    gen_free(gen2);
    func_free();
}

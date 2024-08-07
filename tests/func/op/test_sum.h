#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/sum.h"
#include "../../util/test.h"

void test_sum(void)
{
    Gen *gen = gen_create(sum_create(const_create(0.1)));
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.1);
    assert_double_equal(gen_eval(gen, NULL), 0.2);
    assert_double_equal(gen_eval(gen, NULL), 0.3);
    assert_double_equal(gen_eval(gen, NULL), 0.4);
    gen_free(gen);
    func_free();
}

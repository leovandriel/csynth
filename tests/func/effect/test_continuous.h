#include "../../../src/func/effect/continuous.h"
#include "../../../src/func/effect/loop.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/sum.h"
#include "../../util/test.h"

void test_continuous(void)
{
    Gen *gen = gen_create(loop_create(const_(0.5), continuous_create(sum_create(const_(1)))));
    assert_double_equal(gen_eval(gen, NULL), 0);
    assert_double_equal(gen_eval(gen, NULL), 1);
    assert_double_equal(gen_eval(gen, NULL), 2);
    assert_double_equal(gen_eval(gen, NULL), 3);
    assert_double_equal(gen_eval(gen, NULL), 4);
    gen_free(gen);
    func_free();
}

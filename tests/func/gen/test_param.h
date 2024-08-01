#include "../../../src/func/gen/param.h"
#include "../../util/test.h"

void test_param(void)
{
    Gen *gen = gen_create(param_create(EvalParamPitchTick));
    Eval eval = {0};
    assert_double_equal(gen_eval(gen, &eval), 0);
    eval.params[EvalParamPitchTick] = 0.5;
    assert_double_equal(gen_eval(gen, &eval), 0.5);
    gen_free(gen);
    func_free();
}

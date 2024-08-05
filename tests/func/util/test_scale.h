#include "../../../src/func/gen/param.h"
#include "../../../src/func/util/scale.h"
#include "../../util/test.h"

void test_scale(void)
{
    Gen *gen = gen_create(scale_create(EvalParamPitchTick, const_create(10), param_create(EvalParamPitchTick)));
    Eval eval = {0};
    eval.params[EvalParamPitchTick] = 5;
    assert_long_equal(gen_eval(gen, &eval), 50);
    gen_free(gen);
    func_free();
}

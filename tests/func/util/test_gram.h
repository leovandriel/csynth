#include "../../../src/func/gen/const.h"
#include "../../../src/func/util/gram.h"
#include "../../util/test.h"

void test_gram(void)
{
    Gen *gen = gen_create(gram_create(const_create(1), 8, 8, 1, "output/test.ppm", 1));
    Eval eval = {0};
    eval.params[EvalParamPitchTick] = 1;
    assert_long_equal(gen_eval(gen, &eval), 1);
    gen_free(gen);
    func_free();
}

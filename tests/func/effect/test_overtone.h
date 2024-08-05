#include "../../../src/func/effect/overtone.h"
#include "../../../src/func/gen/saw.h"
#include "../../util/test.h"

void test_overtone(void)
{
    Gen *gen = gen_create(overtone_create(3, const_create(0.5), saw_create(const_create(0.1))));
    Eval eval = {.compute_flag = 1};
    eval.params[EvalParamPitchTick] = 0.1;
    assert_double_equal(gen_eval(gen, &eval), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, &eval), 0.7865493374775741);
    assert_double_equal(gen_eval(gen, &eval), 1.5730986749551481);
    assert_double_equal(gen_eval(gen, &eval), 2.3596480124327224);
    assert_double_equal(gen_eval(gen, &eval), 3.1461973499102962);
    assert_double_equal(gen_eval(gen, &eval), 3.9327466873878696);
    assert_double_equal(gen_eval(gen, &eval), -3.1461973499102962);
    assert_double_equal(gen_eval(gen, &eval), -2.3596480124327224);
    assert_double_equal(gen_eval(gen, &eval), -1.5730986749551481);
    assert_double_equal(gen_eval(gen, &eval), -0.7865493374775742);
    assert_double_equal(gen_eval(gen, &eval), -0.0000000000000002);
    assert_double_equal(gen_eval(gen, &eval), 0.7865493374775737);
    gen_free(gen);
    func_free();
}

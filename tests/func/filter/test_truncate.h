#include "../../../src/func/filter/envelopes.h"
#include "../../../src/func/filter/truncate.h"
#include "../../util/test.h"

void test_truncate_miss()
{
    Func *input = add(rect_env_(0, 0.1), rect_env_(0.5, 0.6));
    Func *trunc = truncate_create(const_(1.25), input);
    Gen *gen = gen_create(trunc);
    Eval eval = {0};
    eval.params[EvalParamPitchTick] = 0.1;
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    gen_free(gen);
}

void test_truncate_hit()
{
    Func *input = add(rect_env_(0, 0.1), rect_env_(0.8, 0.9));
    Func *trunc = truncate_create(const_(1.25), input);
    Gen *gen = gen_create(trunc);
    Eval eval = {0};
    eval.params[EvalParamPitchTick] = 0.1;
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    gen_free(gen);
}

void test_truncate()
{
    test_truncate_miss();
    test_truncate_hit();
    func_free();
}

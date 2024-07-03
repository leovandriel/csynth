#include "../../src/core/gen.h"
#include "../../src/func/gen/const.h"
#include "../../src/func/gen/sine.h"
#include "../../src/func/op/mul.h"
#include "../../src/func/time/ticker.h"
#include "../util/test.h"

void test_gen_count()
{
    Func *input = mul_create(FUNCS(const_(0.5), sine_create(ticker_create(EvalTickNone))));
    Gen *gen = gen_create(input);
    Eval eval = eval_create(0.1);
    assert_long_equal(eval.gen_count, 0);
    gen_eval(gen, &eval);
    assert_long_equal(eval.gen_count, 4);
    gen_eval(gen, &eval);
    assert_long_equal(eval.gen_count, 8);
    gen_free(gen);
    func_free();
}

void test_gen()
{
    test_gen_count();
}

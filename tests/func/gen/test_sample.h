#include "../../../src/func/gen/gens.h"
#include "../../../src/func/gen/sample.h"
#include "../../util/test.h"

void test_sample()
{
    rand_seed(0);
    Func *input = sample();
    Gen *gen = gen_create(input);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), 0.0625038757098120);
    assert_double_equal(gen_eval(gen, &eval), 0.0625038757098120);
    assert_double_equal(gen_eval(gen, &eval), 0.0625038757098120);
    assert_double_equal(gen_eval(gen, &eval), 0.0625038757098120);
    gen_free(gen);
    func_free();
}

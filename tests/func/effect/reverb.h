#include "../../../src/func/effect/effects.h"
#include "../../../src/func/effect/reverb.h"
#include "../../../src/func/gen/gens.h"
#include "../../util/test.h"

void test_reverb()
{
    Func *time = reverb(const_(0.5), const_(0.5), saw_(1));
    Gen *gen = gen_create(time);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, eval), 0.00);
    assert_double_equal(gen_eval(gen, eval), 0.20);
    assert_double_equal(gen_eval(gen, eval), 0.40);
    assert_double_equal(gen_eval(gen, eval), 0.60);
    assert_double_equal(gen_eval(gen, eval), 0.80);
    assert_double_equal(gen_eval(gen, eval), 1.00);
    assert_double_equal(gen_eval(gen, eval), -0.70);
    assert_double_equal(gen_eval(gen, eval), -0.40);
    assert_double_equal(gen_eval(gen, eval), -0.10);
    assert_double_equal(gen_eval(gen, eval), 0.20);
    assert_double_equal(gen_eval(gen, eval), 0.50);
    assert_double_equal(gen_eval(gen, eval), -0.15);
    gen_free(gen);
    func_free();
}

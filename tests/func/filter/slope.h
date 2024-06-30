#include "../../../src/func/filter/filters.h"
#include "../../../src/func/filter/slope.h"
#include "../../../src/func/gen/gens.h"
#include "../../util/test.h"

void test_slope()
{
    Func *output = slope_(1, square_(2));
    Gen *gen = gen_create(output);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, eval), 0.1);
    assert_double_equal(gen_eval(gen, eval), 0.2);
    assert_double_equal(gen_eval(gen, eval), 0.3);
    assert_double_equal(gen_eval(gen, eval), 0.2);
    assert_double_equal(gen_eval(gen, eval), 0.1);
    assert_double_equal(gen_eval(gen, eval), 0.2);
    assert_double_equal(gen_eval(gen, eval), 0.3);
    assert_double_equal(gen_eval(gen, eval), 0.4);
    assert_double_equal(gen_eval(gen, eval), 0.3);
    assert_double_equal(gen_eval(gen, eval), 0.2);
    assert_double_equal(gen_eval(gen, eval), 0.3);
    assert_double_equal(gen_eval(gen, eval), 0.4);
    gen_free(gen);
    func_free();
}

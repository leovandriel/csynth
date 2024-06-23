#include "../../../src/func/filter/slope.h"
#include "../../../src/func/gen/gens.h"
#include "../../util/test.h"

void test_slope()
{
    Func *output = slope(square_(2), const_(1));
    Gen *gen = gen_create(output);
    Eval eval = {.audio_step = 0.1};
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

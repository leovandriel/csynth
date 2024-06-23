#include "../../../src/func/filter/chorus.h"
#include "../../../src/func/gen/gens.h"
#include "../../util/test.h"

void test_chorus()
{
    Func *time = chorus_(sine_(10), sine_(.2), 0.2, 0.2);
    Gen *gen = gen_create(time);
    Eval eval = {.audio_step = 0.1};
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 0.0);
    gen_free(gen);
    func_free();
}

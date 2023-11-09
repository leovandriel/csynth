//
// low_pass.h - A first-order low-pass filter
//
// `low_pass(input, frequency)` with input and frequency functions.
//
#ifndef CSYNTH_LOW_PASS_H
#define CSYNTH_LOW_PASS_H

#include "../../util/math.h"
#include "../../util/test.h"
#include "../../core/func.h"
#include "../gen/const.h"

typedef struct
{
    double output;
} LowPassContext;

static double low_pass_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    LowPassContext *context = (LowPassContext *)context_;
    double input = gen_eval(args[0]);
    double frequency = gen_eval(args[1]);
    double factor = 1 / (PI_M_2 * frequency * delta) + 1.0;
    double output = context->output;
    context->output = context->output + (input - context->output) / factor;
    return output;
}

Func *low_pass(Func *input, Func *frequency)
{
    return func_create(NULL, low_pass_eval, NULL, sizeof(LowPassContext), NULL, 2, input, frequency);
}

Func *low_pass_(Func *input, double frequency) { return low_pass(input, const_(frequency)); }

void test_low_pass()
{
    Func *t = low_pass(const_(1), const_(10));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0000000000000000);
    assert_gen_equal(g, 0.8626974383015871);
    assert_gen_equal(g, 0.9811480065510535);
    assert_gen_equal(g, 0.9974115730063380);
    assert_gen_equal(g, 0.9996446023430009);
    assert_gen_equal(g, 0.9999512029912724);
    assert_gen_equal(g, 0.9999933000456985);
    assert_gen_equal(g, 0.9999990800791111);
    assert_gen_equal(g, 0.9999998736925054);
    assert_gen_equal(g, 0.9999999826576574);
    assert_gen_equal(g, 0.9999999976188519);
    assert_gen_equal(g, 0.9999999996730623);
}

#endif // CSYNTH_LOW_PASS_H

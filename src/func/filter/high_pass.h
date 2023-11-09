//
// high_pass.h - A first-order high-pass filter
//
// `high_pass(input, frequency)` with input and frequency functions.
//
#ifndef CSYNTH_HIGH_PASS_H
#define CSYNTH_HIGH_PASS_H

#include <math.h>

#include "../../util/test.h"
#include "../../core/func.h"
#include "../gen/const.h"

typedef struct
{
    double input;
    double output;
} HighPassContext;

static double high_pass_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    HighPassContext *context = (HighPassContext *)context_;
    double input = gen_eval(args[0]);
    double frequency = gen_eval(args[1]);
    double factor = (2.0 * M_PI * frequency * delta) + 1.0;
    double output = context->output;
    context->output = (context->output + input - context->input) / factor;
    context->input = input;
    return output;
}

Func *high_pass(Func *input, Func *frequency)
{
    return func_create(NULL, high_pass_eval, NULL, sizeof(HighPassContext), NULL, 2, input, frequency);
}

Func *high_pass_(Func *input, double frequency) { return high_pass(input, const_(frequency)); }

void test_high_pass()
{
    Func *t = high_pass(const_(1), const_(10));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0000000000000000);
    assert_gen_equal(g, 0.1373025616984130);
    assert_gen_equal(g, 0.0188519934489465);
    assert_gen_equal(g, 0.0025884269936620);
    assert_gen_equal(g, 0.0003553976569991);
    assert_gen_equal(g, 0.0000487970087276);
    assert_gen_equal(g, 0.0000066999543015);
    assert_gen_equal(g, 0.0000009199208889);
    assert_gen_equal(g, 0.0000001263074946);
    assert_gen_equal(g, 0.0000000173423426);
    assert_gen_equal(g, 0.0000000023811481);
    assert_gen_equal(g, 0.0000000003269377);
}

#endif // CSYNTH_HIGH_PASS_H

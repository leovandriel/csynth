//
// low_pass.h - A first-order low-pass filter
//
// `low_pass(input, frequency)` with input and frequency functions.
//
#ifndef CSYNTH_LOW_PASS_H
#define CSYNTH_LOW_PASS_H

#include <assert.h>
#include <math.h>

#include "../../core/func.h"
#include "../gen/const.h"

typedef struct
{
    double output;
} LowPassContext;

static double low_pass_eval(Gen **args, __attribute__((unused)) int count, double delta, void *context_)
{
    LowPassContext *context = (LowPassContext *)context_;
    double input = gen_eval(args[0]);
    double frequency = gen_eval(args[1]);
    double factor = 1 / (2.0 * M_PI * frequency * delta) + 1.0;
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
    double epsilon = 1e-4;
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.862697) < epsilon);
    assert(fabs(gen_eval(g) - 0.981148) < epsilon);
    assert(fabs(gen_eval(g) - 0.997412) < epsilon);
    assert(fabs(gen_eval(g) - 0.999645) < epsilon);
    assert(fabs(gen_eval(g) - 0.999951) < epsilon);
    assert(fabs(gen_eval(g) - 0.999993) < epsilon);
    assert(fabs(gen_eval(g) - 0.999999) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
}

#endif // CSYNTH_LOW_PASS_H

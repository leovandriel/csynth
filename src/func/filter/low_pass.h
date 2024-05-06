//
// low_pass.h - A first-order low-pass filter
//
// `low_pass(input, frequency)` with input and frequency functions.
//
#ifndef CSYNTH_LOW_PASS_H
#define CSYNTH_LOW_PASS_H

#include "../../core/func.h"
#include "../../util/math.h"
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
    return func_create(NULL, low_pass_eval, NULL, sizeof(LowPassContext), NULL, FUNC_FLAG_DEFAULT, 2, input, frequency);
}

Func *low_pass_(Func *input, double frequency) { return low_pass(input, const_(frequency)); }

#endif // CSYNTH_LOW_PASS_H

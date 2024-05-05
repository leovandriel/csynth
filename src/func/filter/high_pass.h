//
// high_pass.h - A first-order high-pass filter
//
// `high_pass(input, frequency)` with input and frequency functions.
//
#ifndef CSYNTH_HIGH_PASS_H
#define CSYNTH_HIGH_PASS_H

#include "../../util/math.h"
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
    double factor = (PI_M_2 * frequency * delta) + 1.0;
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

#endif // CSYNTH_HIGH_PASS_H

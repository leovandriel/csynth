//
// step.h - A step function
//
// `step(at)` returns 1 if time is past at, otherwise 0.
//
#ifndef CSYNTH_STEP_H
#define CSYNTH_STEP_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

static double step_eval(__attribute__((unused)) int count, Gen **args, __attribute__((unused)) double delta, __attribute__((unused)) void *context_)
{
    double input = gen_eval(args[0]);
    double edge = gen_eval(args[1]);
    double value = input < edge ? 0.0 : 1.0;
    return value;
}

Func *step_op(Func *input, Func *edge)
{
    return func_create(NULL, step_eval, NULL, 0, NULL, FUNC_FLAG_DEFAULT, 2, input, edge);
}
Func *step_op_(Func *input, double edge) { return step_op(input, const_(edge)); }

#endif // CSYNTH_STEP_H

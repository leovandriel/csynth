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

static double step_eval(__U int count, Gen **args, Eval eval, __U void *context_)
{
    double edge = gen_eval(args[0], eval);
    double input = gen_eval(args[1], eval);
    double value = input < edge ? 0.0 : 1.0;
    return value;
}

Func *step_op(Func *edge, Func *input)
{
    return func_create(NULL, step_eval, NULL, 0, NULL, FuncFlagNone, FUNCS(edge, input));
}
Func *step_op_(double edge, Func *input) { return step_op(const_(edge), input); }

#endif // CSYNTH_STEP_H

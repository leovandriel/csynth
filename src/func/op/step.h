#ifndef CSYNTH_STEP_H
#define CSYNTH_STEP_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double step_eval(__U size_t count, Gen **args, Eval *eval, __U void *context_)
{
    double edge = gen_eval(args[0], eval);
    double input = gen_eval(args[1], eval);
    double value = input < edge ? 0.0 : 1.0;
    return value;
}

/**
 * @brief Create a function for the step function, i.e. 0 if input < edge,
 * otherwise 1.
 *
 * @param edge Edge value.
 * @param input Input value.
 * @return Func* Step function.
 */
Func *step_create(Func *edge, Func *input)
{
    return func_create(NULL, step_eval, NULL, NULL, 0, NULL, FuncFlagNone, edge, input);
}

#endif // CSYNTH_STEP_H

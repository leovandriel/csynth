#ifndef CSYNTH_CONTINUOUS_H
#define CSYNTH_CONTINUOUS_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double continuous_eval(__U size_t count, Gen **args, Eval *eval, __U void *context)
{
    return gen_eval(args[0], eval);
}

/**
 * @brief Wrap a function to prevent it from being reset.
 *
 * Funcs can call `gen_reset` on their input to revert the state, e.g. in `loop`
 * to allow for looping. The `continuous` func prevents the propagation of such
 * a reset, allowing the func argument to continue independently of such a loop.
 * This allows for combining looped and non-looped funcs in cases where nesting
 * is required. See `dynamic.c` for an example.
 *
 * @param input Input function to wrap.
 * @return Func* Continuous function.
 */
Func *continuous_create(Func *input)
{
    return func_create(NULL, continuous_eval, NULL, NULL, 0, NULL, FuncFlagStopReset, input);
}

#endif // CSYNTH_CONTINUOUS_H

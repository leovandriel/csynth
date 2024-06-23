//
// continuous.h - Prevents its input from being reset
//
// Funcs can call `gen_reset` on their input to revert the state, e.g. in `loop`
// to allow for looping. The `continuous` func prevents the propagation of such
// a reset, allowing the func argument to continue independently of such a loop.
// This allows for combining looped and non-looped funcs in cases where nesting
// is required. See `dynamic.c` for an example.
//
// `continuous(input)`
//
#ifndef CSYNTH_CONTINUOUS_H
#define CSYNTH_CONTINUOUS_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double continuous_eval(__U int count, Gen **args, __U double delta, __U void *context)
{
    return gen_eval(args[0]);
}

Func *continuous(Func *input)
{
    return func_create(NULL, continuous_eval, NULL, 0, NULL, FUNC_FLAG_STOP_RESET, 1, input);
}

#endif // CSYNTH_CONTINUOUS_H

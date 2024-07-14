//
// const.h - A constant value function.
//
// `const_(value)` takes one value, which it will return during sampling. Primary
// purpose is wrapping doubles in a Func, so it can be used as argument for
// other functions.
//
// For convenience, the macro `_(value)` is provided, which is equal to
// `const_(value)`.
// - ZERO - A constant function, which always returns 0
// - ONE - A constant function, which always returns 1
//
#ifndef CSYNTH_CONST_H
#define CSYNTH_CONST_H

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    double value;
} ConstContext;

static double const_eval(__U size_t count, __U Gen **args, __U Eval *eval, void *context_)
{
    ConstContext *context = (ConstContext *)context_;
    return context->value;
}

Func *const_create(double value)
{
    ConstContext initial = {.value = value};
    return func_create(NULL, const_eval, NULL, sizeof(ConstContext), &initial, FuncFlagNone, ARGS());
}

Func *const_(double value) { return const_create(value); }
Func *_(double value) { return const_(value); }

#endif // CSYNTH_CONST_H

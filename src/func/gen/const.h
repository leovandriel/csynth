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

/**
 * @brief Create a function of constant value.
 *
 * @param value double Value to be returned during sampling.
 * @return Func* Function object.
 */
Func *const_create(double value)
{
    ConstContext initial = {.value = value};
    return func_create(NULL, const_eval, NULL, sizeof(ConstContext), &initial, FuncFlagNone);
}

Func *const_(double value) { return const_create(value); }
Func *_(double value) { return const_(value); }

#endif // CSYNTH_CONST_H

#ifndef CSYNTH_CONST_H
#define CSYNTH_CONST_H

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see const_create */
typedef struct
{
    /** @brief Constant value. */
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
 * @param value Value to be returned during sampling.
 * @return Func* Const function.
 */
Func *const_create(double value)
{
    ConstContext initial = {.value = value};
    return func_create(NULL, const_eval, NULL, NULL, sizeof(ConstContext), &initial, FuncFlagNone);
}

/** @brief Shorthand for `const_create`. */
Func *const_(double value) { return const_create(value); }
/** @brief Shorthand for `const_create`. */
Func *_(double value) { return const_(value); }

#endif // CSYNTH_CONST_H

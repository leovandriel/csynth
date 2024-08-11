#ifndef CSYNTH_IMPULSE_H
#define CSYNTH_IMPULSE_H

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see impulse_create */
typedef struct
{
    /** @brief Flag to indicate impulse completed. */
    bool completed;
} ImpuseContext;

static double impulse_eval(__U size_t count, __U Gen **args, __U Eval *eval, void *context_)
{
    ImpuseContext *context = (ImpuseContext *)context_;
    if (!context->completed)
    {
        context->completed = true;
        return 1.0;
    }
    return 0.0;
}

/**
 * @brief Create a function that outputs 1 once, and 0 after.
 *
 * Represents a single impulse, like Dirac delta function.
 *
 * @return Func* Impulse function.
 */
Func *impulse_create(void)
{
    return func_create(NULL, impulse_eval, NULL, NULL, sizeof(ImpuseContext), NULL, FuncFlagNone);
}

#endif // CSYNTH_IMPULSE_H

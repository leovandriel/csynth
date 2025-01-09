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
 * Represents a single impulse, similar to a discrete-time Dirac delta function.
 * When first evaluated, the function outputs 1.0, then outputs 0.0 for all
 * subsequent evaluations. This creates an impulse response that can be used to
 * test system behavior, trigger events, or initialize state.
 *
 * Example usage:
 * - Triggering envelope generators or filters
 * - Testing system impulse response
 * - Initializing delay lines or feedback paths
 * - Creating click/pop sounds for percussion synthesis
 *
 * @return Func* Impulse function that outputs 1.0 on first evaluation and 0.0
 * after.
 */
Func *impulse_create(void)
{
    return func_create(NULL, impulse_eval, NULL, NULL, sizeof(ImpuseContext), NULL, FuncFlagNone);
}

#endif // CSYNTH_IMPULSE_H

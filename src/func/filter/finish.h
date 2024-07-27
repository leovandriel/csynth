#ifndef CSYNTH_FINISH_H
#define CSYNTH_FINISH_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see finish_create */
typedef struct
{
    /** @brief Decay of level threshold. */
    double decay;
    /** @brief Current level, subject decay. */
    double level;
} FinishContext;

static double finish_eval(__U size_t count, __U Gen **args, Eval *eval, void *context_)
{
    FinishContext *context = (FinishContext *)context_;
    if (context->level < FUNC_AUDIBLE)
    {
        return 0.0;
    }
    double tick = gen_eval(args[0], eval);
    double input = gen_eval(args[1], eval);
    if (eval == NULL || eval->compute_flag)
    {
        context->decay = exp2(tick);
    }
    context->level = fmax(fabs(input), context->level / context->decay);
    return input * context->level;
}

/**
 * @brief Create a function that permanently snaps to zero if extended silence
 * is detected.
 *
 * @param tick Periods per sample.
 * @param input Input signal.
 * @return Func* Finish function.
 */
Func *finish_create(Func *tick, Func *input)
{
    FinishContext initial = {.level = 1.0};
    return func_create(NULL, finish_eval, NULL, sizeof(FinishContext), &initial, FuncFlagNone, tick, input);
}

#endif // CSYNTH_FINISH_H

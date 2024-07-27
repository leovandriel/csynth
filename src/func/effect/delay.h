#ifndef CSYNTH_DELAY_H
#define CSYNTH_DELAY_H

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see delay_create */
typedef struct
{
    /** @brief Time delay. */
    double time;
} DelayContext;

static double delay_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    DelayContext *context = (DelayContext *)context_;
    double tick = gen_eval(args[0], eval);
    double output = 0.0;
    while (context->time >= 1)
    {
        output = gen_eval(args[1], eval);
        context->time -= tick;
    }
    context->time += tick;
    return output;
}

/**
 * @brief Create function to delay the sampling of an input function.
 *
 * Until the duration function is reached, the output will be 0. After that, the
 * input function will be sampled. Negative delay will skip the first samples,
 * i.e. fast-forward the input.
 *
 * @param tick Periods per sample
 * @param input Input function to delay.
 * @return Func* Delay function.
 */
Func *delay_create(Func *tick, Func *input)
{
    return func_create(NULL, delay_eval, NULL, sizeof(DelayContext), NULL, FuncFlagNone, tick, input);
}

#endif // CSYNTH_DELAY_H

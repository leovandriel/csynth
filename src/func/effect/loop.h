#ifndef CSYNTH_LOOP_H
#define CSYNTH_LOOP_H

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see loop_create */
typedef struct
{
    /** @brief Phase accumulator. */
    double phase;
} LoopContext;

static double loop_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    LoopContext *context = (LoopContext *)context_;
    if (context->phase >= 1.0)
    {
        context->phase -= 1.0;
        gen_reset(args[1]);
    }
    double tick = gen_eval(args[0], eval);
    double input = gen_eval(args[1], eval);
    context->phase += tick;
    return input;
}

/**
 * @brief Create function to loop the sampling of an input function.
 *
 * After a full period, the input function is reset, looping the input from the
 * start.
 *
 * @param tick Periods per sample.
 * @param input Input function to loop.
 * @return Func* Loop function
 */
Func *loop_create(Func *tick, Func *input)
{
    return func_create(NULL, loop_eval, NULL, sizeof(LoopContext), NULL, FuncFlagNone, tick, input);
}

#endif // CSYNTH_LOOP_H

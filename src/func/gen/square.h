#ifndef CSYNTH_SQUARE_H
#define CSYNTH_SQUARE_H

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see square_create */
typedef struct
{
    /** @brief Time offset within 1s period. */
    double phase;
    /** @brief Current output value. */
    double output;
} SquareContext;

static double square_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    SquareContext *context = (SquareContext *)context_;
    if (context->phase >= 0.5)
    {
        context->phase -= 0.5;
        context->output = -context->output;
    }
    double tick = gen_eval(args[0], eval);
    context->phase += tick;
    return context->output;
}

/**
 * @brief Create a function that outputs a square wave.
 *
 * @param tick Periods per sample.
 * @return Func* Square function.
 */
Func *square_create(Func *tick)
{
    SquareContext initial = {.output = 1.0};
    return func_create(NULL, square_eval, NULL, sizeof(SquareContext), &initial, FuncFlagNone, tick);
}

#endif // CSYNTH_SQUARE_H

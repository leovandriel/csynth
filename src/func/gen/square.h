//
// square.h - A square function
//
// `square(frequency)` returns a square wave with the given frequency.
//
#ifndef CSYNTH_SQUARE_H
#define CSYNTH_SQUARE_H

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    double time;
    double output;
} SquareContext;

static double square_eval(__U int count, Gen **args, Eval *eval, void *context_)
{
    SquareContext *context = (SquareContext *)context_;
    if (context->time >= 0.5)
    {
        context->time -= 0.5;
        context->output = -context->output;
    }
    double tick = gen_eval(args[0], eval);
    context->time += tick;
    return context->output;
}

Func *square_create(Func *tick)
{
    SquareContext initial = {.output = 1.0};
    return func_create(NULL, square_eval, NULL, sizeof(SquareContext), &initial, FuncFlagNone, FUNCS(tick));
}

#endif // CSYNTH_SQUARE_H

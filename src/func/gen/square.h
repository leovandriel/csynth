//
// square.h - A square function
//
// `square(frequency)` returns a square wave with the given frequency.
//
#ifndef CSYNTH_SQUARE_H
#define CSYNTH_SQUARE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "./const.h"

typedef struct
{
    double time;
    double output;
} SquareContext;

static double square_eval(__U int count, Gen **args, double delta, void *context_)
{
    SquareContext *context = (SquareContext *)context_;
    double span = 1.0 / (gen_eval(args[0]) * 2.0);
    if (context->time >= span)
    {
        context->time -= span;
        context->output = -context->output;
    }
    context->time += delta;
    return context->output;
}

Func *square(Func *frequency)
{
    SquareContext initial = (SquareContext){
        .output = 1.0,
    };
    return func_create(NULL, square_eval, NULL, sizeof(SquareContext), &initial, FuncFlagNone, 1, frequency);
}

Func *square_(double frequency) { return square(const_(frequency)); }

#endif // CSYNTH_SQUARE_H

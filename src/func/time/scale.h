//
// scale.h - Time scaling
//
#ifndef CSYNTH_SCALE_H
#define CSYNTH_SCALE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

typedef struct
{
    EvalTick tick;
} ScaleContext;

static double scale_eval(__U int count, __U Gen **args, Eval eval, void *context_)
{
    ScaleContext *context = (ScaleContext *)context_;
    double factor = gen_eval(args[0], eval);
    eval.tick[context->tick] *= factor;
    double input = gen_eval(args[1], eval);
    return input;
}

Func *scale(EvalTick tick, Func *factor, Func *input)
{
    ScaleContext initial = {.tick = tick};
    return func_create(NULL, scale_eval, NULL, sizeof(ScaleContext), &initial, FuncFlagNone, FUNCS(factor, input));
}

Func *scale_(EvalTick tick, double factor, Func *input) { return scale(tick, const_(factor), input); }

#endif // CSYNTH_SCALE_H

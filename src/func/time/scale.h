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
    eval.tick[context->tick] *= gen_eval(args[0], eval);
    return gen_eval(args[1], eval);
}

Func *scale(EvalTick tick, Func *factor, Func *input)
{
    ScaleContext initial = {.tick = tick};
    return func_create(NULL, scale_eval, NULL, sizeof(ScaleContext), &initial, FuncFlagNone, FUNCS(factor, input));
}

Func *scale_(EvalTick tick, double factor, Func *input) { return scale(tick, input, const_(factor)); }

#endif // CSYNTH_SCALE_H

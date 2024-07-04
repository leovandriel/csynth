//
// scale.h - Time scaling
//
#ifndef CSYNTH_SCALE_H
#define CSYNTH_SCALE_H

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    EvalTick tick;
} ScaleContext;

static double scale_eval(__U size_t count, __U Gen **args, Eval *eval, void *context_)
{
    ScaleContext *context = (ScaleContext *)context_;
    double factor = gen_eval(args[0], eval);
    double restore = eval->tick[context->tick];
    eval->tick[context->tick] = restore * factor;
    double input = gen_eval(args[1], eval);
    eval->tick[context->tick] = restore;
    return input;
}

Func *scale_create(EvalTick tick, Func *factor, Func *input)
{
    ScaleContext initial = {.tick = tick};
    return func_create(NULL, scale_eval, NULL, sizeof(ScaleContext), &initial, FuncFlagNone, FUNCS(factor, input));
}

#endif // CSYNTH_SCALE_H

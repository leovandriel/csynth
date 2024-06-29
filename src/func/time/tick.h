//
// tick.h - Sampling interval
//
#ifndef CSYNTH_TICK_H
#define CSYNTH_TICK_H

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    EvalTick tick;
} TickerContext;

static double tick_eval(__U int count, __U Gen **args, Eval eval, void *context_)
{
    TickerContext *context = (TickerContext *)context_;
    return eval.tick[context->tick];
}

Func *tick(EvalTick tick)
{
    TickerContext initial = {.tick = tick};
    return func_create(NULL, tick_eval, NULL, sizeof(TickerContext), &initial, FuncFlagNone, FUNCS());
}

#endif // CSYNTH_TICK_H

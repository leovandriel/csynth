//
// ticker.h - Sampling interval
//
#ifndef CSYNTH_TICKER_H
#define CSYNTH_TICKER_H

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    EvalTick tick;
} TickerContext;

static double ticker_eval(__U int count, __U Gen **args, Eval *eval, void *context_)
{
    TickerContext *context = (TickerContext *)context_;
    return eval->tick[context->tick];
}

Func *ticker_create(EvalTick tick)
{
    TickerContext initial = {.tick = tick};
    return func_create(NULL, ticker_eval, NULL, sizeof(TickerContext), &initial, FuncFlagNone, FUNCS());
}

#endif // CSYNTH_TICKER_H

//
// eval.h - An interface for evaluating functions.
//
#ifndef CSYNTH_EVAL_H
#define CSYNTH_EVAL_H

#include "./def.h"

Eval eval_create(double value)
{
    Eval eval = {.wall_tick = value};
    for (EvalTick tick = EvalTickNone; tick < EvalTickLength; tick++)
    {
        eval.tick[tick] = value;
    }
    return eval;
}

#endif // CSYNTH_EVAL_H

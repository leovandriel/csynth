//
// eval.h - An interface for evaluating functions.
//
#ifndef CSYNTH_EVAL_H
#define CSYNTH_EVAL_H

#include "./def.h"

Eval eval_create(double tick)
{
    Eval eval = {.wall_tick = tick};
    for (EvalParam param = EvalParamNone; param < EvalParamLength; param++)
    {
        eval.params[param] = tick;
    }
    return eval;
}

#endif // CSYNTH_EVAL_H

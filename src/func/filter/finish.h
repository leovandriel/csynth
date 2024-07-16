//
// finish.h - Permanently snaps to zero if extended silence is detected
//
#ifndef CSYNTH_FINISH_H
#define CSYNTH_FINISH_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    double tick_exp;
    double level;
} FinishContext;

static double finish_eval(__U size_t count, __U Gen **args, Eval *eval, void *context_)
{
    FinishContext *context = (FinishContext *)context_;
    if (context->level < FUNC_AUDIBLE)
    {
        return 0.0;
    }
    double tick = gen_eval(args[0], eval);
    double input = gen_eval(args[1], eval);
    if (eval == NULL || eval->compute_flag)
    {
        context->tick_exp = exp2(tick);
    }
    context->level = fmax(fabs(input), context->level / context->tick_exp);
    return input * context->level;
}

Func *finish_create(Func *tick, Func *input)
{
    FinishContext initial = {.level = 1.0};
    return func_create(NULL, finish_eval, NULL, sizeof(FinishContext), &initial, FuncFlagNone, ARGS(tick, input));
}

#endif // CSYNTH_FINISH_H

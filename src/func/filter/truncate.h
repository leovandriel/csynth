//
// truncate.h - Permanently snaps to zero if extended silence is detected
//
#ifndef CSYNTH_TRUNCATE_H
#define CSYNTH_TRUNCATE_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    double level;
} TruncateContext;

static double truncate_eval(__U int count, __U Gen **args, EvalContext *eval, void *context_)
{
    TruncateContext *context = (TruncateContext *)context_;
    if (context->level < FUNC_AUDIBLE)
    {
        return 0.0;
    }
    double tick = gen_eval(args[0], eval);
    double input = gen_eval(args[1], eval);
    context->level = fmax(fabs(input), context->level / exp2(tick));
    return input * context->level;
}

Func *truncate_create(Func *tick, Func *input)
{
    TruncateContext initial = {.level = 1.0};
    return func_create(NULL, truncate_eval, NULL, sizeof(TruncateContext), &initial, FuncFlagNone, FUNCS(tick, input));
}

#endif // CSYNTH_TRUNCATE_H

//
// truncate.h - Permanently snaps to zero if extended silence is detected
//
#ifndef CSYNTH_TRUNCATE_H
#define CSYNTH_TRUNCATE_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

#define TRUNCATE_DEFAULT_DECAY 0.1 // 10%/sec

typedef struct
{
    double level;
} TruncateContext;

static double truncate_eval(__U int count, __U Gen **args, Eval eval, void *context_)
{
    TruncateContext *context = (TruncateContext *)context_;
    if (context->level < FUNC_AUDIBLE)
    {
        return 0.0;
    }
    double output = gen_eval(args[0], eval);
    double decay = gen_eval(args[1], eval);
    context->level = fmax(fabs(output), context->level * pow(decay, eval.tick[EvalTickPitch]));
    return output * context->level;
}

Func *truncate(Func *input, Func *decay)
{
    TruncateContext initial = {
        .level = 1.0,
    };
    return func_create(NULL, truncate_eval, NULL, sizeof(TruncateContext), &initial, FuncFlagNone, FUNCS(input, decay));
}

Func *truncate_(Func *input, double decay)
{
    return truncate(input, const_(decay));
}

Func *trunc_(Func *input)
{
    return truncate_(input, TRUNCATE_DEFAULT_DECAY);
}

#endif // CSYNTH_TRUNCATE_H

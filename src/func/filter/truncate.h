//
// truncate.h - Permanently snaps to zero if extended silence is detected
//
#ifndef CSYNTH_TRUNCATE_H
#define CSYNTH_TRUNCATE_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

#define TRUNCATE_DEFAULT_DECAY 0.1

typedef struct
{
    double level;
} TruncateContext;

static double truncate_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    TruncateContext *context = (TruncateContext *)context_;
    if (context->level < FUNC_AUDIBLE)
    {
        return 0.0;
    }
    double output = gen_eval(args[0]);
    double decay = gen_eval(args[1]);
    context->level = fmax(fabs(output), context->level * pow(decay, delta));
    return output * context->level;
}

Func *truncate(Func *input, Func *decay)
{
    TruncateContext initial = (TruncateContext){
        .level = 1.0,
    };
    return func_create(NULL, truncate_eval, NULL, sizeof(TruncateContext), &initial, FUNC_FLAG_DEFAULT, 2, input, decay);
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
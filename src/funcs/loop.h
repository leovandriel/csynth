#ifndef COMPOSER_LOOP_H
#define COMPOSER_LOOP_H

#include "../core/func.h"

typedef struct
{
    unsigned long index;
} LoopContext;

double loop_eval(unsigned long index, int rate, Func **args, __attribute__((unused)) int count, void *_context)
{
    LoopContext *context = (LoopContext *)_context;
    unsigned long duration = func_eval(args[1], index, rate) * rate;
    if (index >= context->index + duration)
    {
        context->index = index;
        func_init(args[0], rate);
    }
    double output = func_eval(args[0], index - context->index, rate);
    return output;
}

Func *loop(Func *input, Func *duration)
{
    return func_create(NULL, loop_eval, NULL, sizeof(LoopContext), NULL, 2, input, duration);
}

#endif // COMPOSER_LOOP_H

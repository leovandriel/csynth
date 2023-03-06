#ifndef COMPOSER_SQUARE_H
#define COMPOSER_SQUARE_H

#include "../core/func.h"

typedef struct
{
    double output;
    double index;
} SquareContext;

double square_eval(unsigned long index, int rate, Func **args, __attribute__((unused)) int count, void *_context)
{
    SquareContext *context = (SquareContext *)_context;
    unsigned long span = rate / (func_eval(args[0], index, rate) * 2.0);
    if (index >= context->index + span)
    {
        context->index = index;
        context->output = -context->output;
    }
    return context->output;
}

Func *square(Func *frequency)
{
    SquareContext initial = (SquareContext){
        .output = 1.0,
    };
    return func_create(NULL, square_eval, NULL, sizeof(SquareContext), &initial, 1, frequency);
}

#endif // COMPOSER_SQUARE_H

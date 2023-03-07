#ifndef COMPOSER_TRIANGLE_H
#define COMPOSER_TRIANGLE_H

#include "../core/func.h"

typedef struct
{
    double last;
    double direction;
} TriangleContext;

double triangle_eval(unsigned long index, double rate, Func **args, __attribute__((unused)) int count, void *_context)
{
    TriangleContext *context = (TriangleContext *)_context;
    double frequency = func_eval(args[0], index, rate);
    context->last += context->direction * frequency / rate;
    if (context->last > 1.0)
    {
        context->last = 2.0 - context->last;
        context->direction = -context->direction;
    }
    else if (context->last < -1.0)
    {
        context->last = -2.0 - context->last;
        context->direction = -context->direction;
    }
    return context->last;
}

Func *triangle(Func *frequency)
{
    TriangleContext initial = (TriangleContext){
        .direction = 4.0,
    };
    return func_create(NULL, triangle_eval, NULL, sizeof(TriangleContext), &initial, 1, frequency);
}

#endif // COMPOSER_TRIANGLE_H

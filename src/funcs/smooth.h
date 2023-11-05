#ifndef COMPOSER_SMOOTH_H
#define COMPOSER_SMOOTH_H

#include <math.h>

#include "../core/func.h"

typedef struct
{
    double time;
} SmoothContext;

double smooth_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    SmoothContext *context = (SmoothContext *)_context;
    double edge0 = gen_eval(args[0]);
    double edge1 = gen_eval(args[1]);
    if (context->time <= edge0)
    {
        context->time += delta;
        return 0.0;
    }
    else if (context->time >= edge1)
    {
        context->time += delta;
        return 1.0;
    }
    else
    {
        double s = (context->time - edge0) / (edge1 - edge0);
        context->time += delta;
        return s * s * (3.0 - 2.0 * s);
    }
}

Func *smooth(Func *edge0, Func *edge1)
{
    return func_create(NULL, smooth_eval, NULL, sizeof(SmoothContext), NULL, 2, edge0, edge1);
}

#endif // COMPOSER_SMOOTH_H

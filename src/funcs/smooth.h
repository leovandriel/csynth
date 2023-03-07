#ifndef COMPOSER_SMOOTH_H
#define COMPOSER_SMOOTH_H

#include <math.h>

#include "../core/func.h"

double smooth_eval(unsigned long index, double rate, Func **args, __attribute__((unused)) int count, __attribute__((unused)) void *context)
{
    unsigned long edge0 = round(func_eval(args[0], index, rate) * rate);
    unsigned long edge1 = round(func_eval(args[1], index, rate) * rate);
    if (index < edge0)
    {
        return 0.0;
    }
    else if (index >= edge1)
    {
        return 1.0;
    }
    else
    {
        double s = (double)(index - edge0) / (edge1 - edge0);
        return s * s * (3.0 - 2.0 * s);
    }
}

Func *smooth(Func *edge0, Func *edge1)
{
    return func_create(NULL, smooth_eval, NULL, 0, NULL, 2, edge0, edge1);
}

#endif // COMPOSER_SMOOTH_H

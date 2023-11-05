#ifndef COMPOSER_COMP_H
#define COMPOSER_COMP_H

#include <math.h>
#include <stdarg.h>

#include "../core/func.h"

typedef struct
{
    int rel_abs;
    int index;
    double time;
} CompContext;

double comp_eval(Func **args, int count, double delta, void *_context)
{
    CompContext *context = (CompContext *)_context;
    double lower = 0;
    for (int index = 0; index < count / 2; index++)
    {
        double span = func_eval(args[index * 2 + 1]);
        double upper = context->rel_abs ? lower + span : span;
        if (context->time >= lower && context->time < upper)
        {
            if (context->index != index)
            {
                func_init(args[index * 2], delta);
                context->index = index;
            }
            context->time += delta;
            return func_eval(args[index * 2]);
        }
        lower = upper;
    }
    context->time += delta;
    return 0.0;
}

Func *comp_abs(int count, ...)
{
    CompContext context = (CompContext){
        .rel_abs = 0,
        .index = -1,
    };
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, comp_eval, NULL, sizeof(CompContext), &context, count, valist);
    va_end(valist);
    return func;
}

Func *comp(int count, ...)
{
    CompContext context = (CompContext){
        .rel_abs = 1,
        .index = -1,
    };
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, comp_eval, NULL, sizeof(CompContext), &context, count, valist);
    va_end(valist);
    return func;
}

Func *comp_args(int count, Func **args)
{
    CompContext context = (CompContext){
        .rel_abs = 1,
        .index = -1,
    };
    return func_create_args(NULL, comp_eval, NULL, sizeof(CompContext), &context, count, args);
}

#endif // COMPOSER_COMP_H

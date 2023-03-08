#ifndef COMPOSER_COMP_H
#define COMPOSER_COMP_H

#include <math.h>
#include <stdarg.h>

#include "../core/func.h"

typedef struct
{
    int rel_abs;
    int item;
    unsigned long index;
} CompContext;

double comp_eval(unsigned long index, double rate, Func **args, int count, void *_context)
{
    CompContext *context = (CompContext *)_context;
    unsigned long lower = 0;
    for (int item = 0; item < count / 2; item++)
    {
        unsigned long span = round(func_eval(args[item * 2 + 1], index, rate) * rate);
        double upper = context->rel_abs ? lower + span : span;
        if (index >= lower && index < upper)
        {
            if (context->item != item)
            {
                func_init(args[item * 2], rate);
                context->item = item;
                context->index = index;
            }
            return func_eval(args[item * 2], index - context->index, rate);
        }
        lower = upper;
    }
    return 0.0;
}

Func *comp_abs(int count, ...)
{
    CompContext context = (CompContext){
        .rel_abs = 0,
        .item = -1,
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
        .item = -1,
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
        .item = -1,
    };
    return func_create_args(NULL, comp_eval, NULL, sizeof(CompContext), &context, count, args);
}

#endif // COMPOSER_COMP_H

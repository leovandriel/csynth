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

Func *comp_abs_args(int count, ...)
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

#define comp_abs(...) comp_abs_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__)

Func *comp_rel_args(int count, ...)
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

#define comp_rel(...) comp_rel_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__)
#define comp(...) comp_rel(__VA_ARGS__)

Func *comp_abs_array(int count, Func **args)
{
    CompContext context = (CompContext){
        .rel_abs = 0,
        .index = -1,
    };
    return func_create_array(NULL, comp_eval, NULL, sizeof(CompContext), &context, count, args);
}

Func *comp_rel_array(int count, Func **args)
{
    CompContext context = (CompContext){
        .rel_abs = 1,
        .index = -1,
    };
    return func_create_array(NULL, comp_eval, NULL, sizeof(CompContext), &context, count, args);
}

#endif // COMPOSER_COMP_H

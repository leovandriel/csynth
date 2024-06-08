//
// func.h - An interface for defining functions.
//
#ifndef CSYNTH_FUNC_H
#define CSYNTH_FUNC_H

#include <float.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "./def.h"

static const double EPSILON = DBL_EPSILON * 2;

Func *func_create_int(init_cb init, eval_cb eval, free_cb free, size_t size, void *blank, int count, unsigned int flags)
{
    void *initial = size > 0 && blank != NULL ? calloc(1, size) : NULL;
    if (initial != NULL && blank != NULL)
    {
        memcpy(initial, blank, size);
    }
    Func **args = count > 0 ? (Func **)calloc(count, sizeof(Func *)) : NULL;
    Func *func = (Func *)calloc(1, sizeof(Func));
    *func = (Func){
        .args = args,
        .count = count,
        .size = size,
        .initial = initial,
        .init = init,
        .eval = eval,
        .free = free,
        .flags = flags,
    };
    return func;
}

Func *func_create_array(init_cb init, eval_cb eval, free_cb free, size_t size, void *context, unsigned int flags, int count, Func **args)
{
    Func *func = func_create_int(init, eval, free, size, context, count, flags);
    if (func->args)
    {
        memcpy(func->args, args, count * sizeof(Func *));
    }
    return func;
}

Func *func_create_va(init_cb init, eval_cb eval, free_cb free, size_t size, void *context, unsigned int flags, int count, va_list valist)
{
    Func *func = func_create_int(init, eval, free, size, context, count, flags);
    for (int i = 0; i < count; i++)
    {
        func->args[i] = va_arg(valist, Func *);
    }
    return func;
}

Func *func_create(init_cb init, eval_cb eval, free_cb free, size_t size, void *context, unsigned int flags, int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(init, eval, free, size, context, flags, count, valist);
    va_end(valist);
    return func;
}

#endif // CSYNTH_FUNC_H

//
// func.h - An interface for defining functions.
//
#ifndef CSYNTH_FUNC_H
#define CSYNTH_FUNC_H

#include <float.h>
#include <stdarg.h>
#include <string.h>

#include "../mem/alloc.h"
#include "./def.h"

static const double EPSILON = DBL_EPSILON * 2;

Func *func_list = NULL;

Func *func_create_int(init_callback init, eval_callback eval, free_callback free, size_t size, void *context, unsigned int flags, int count)
{
    void *initial = size > 0 && context != NULL ? calloc_(1, size) : NULL;
    if (initial != NULL && context != NULL)
    {
        memcpy(initial, context, size);
    }
    Func **args = count > 0 ? (Func **)calloc_(count, sizeof(Func *)) : NULL;
    Func *func = (Func *)calloc_(1, sizeof(Func));
    *func = (Func){
        .args = args,
        .count = count,
        .size = size,
        .initial = initial,
        .init = init,
        .eval = eval,
        .free = free,
        .flags = flags,
        .next = func_list,
    };
    func_list = func;
    return func;
}

Func *func_create_array(init_callback init, eval_callback eval, free_callback free, size_t size, void *context, unsigned int flags, int count, Func **args)
{
    Func *func = func_create_int(init, eval, free, size, context, flags, count);
    if (func->args)
    {
        memcpy(func->args, args, count * sizeof(Func *));
    }
    return func;
}

Func *func_create_va(init_callback init, eval_callback eval, free_callback free, size_t size, void *context, unsigned int flags, int count, va_list valist)
{
    Func *func = func_create_int(init, eval, free, size, context, flags, count);
    for (int i = 0; i < count; i++)
    {
        func->args[i] = va_arg(valist, Func *);
    }
    return func;
}

Func *func_create(init_callback init, eval_callback eval, free_callback free, size_t size, void *context, unsigned int flags, int count, ...)
{
    va_list valist = {0};
    va_start(valist, count);
    Func *func = func_create_va(init, eval, free, size, context, flags, count, valist);
    va_end(valist);
    return func;
}

void func_free()
{
    while (func_list != NULL)
    {
        Func *func = func_list;
        func_list = func->next;
        if (func->args != NULL)
        {
            free_(func->args);
        }
        if (func->initial != NULL)
        {
            free_(func->initial);
        }
        free_(func);
    }
}

#endif // CSYNTH_FUNC_H

#ifndef COMPOSER_FUNC_H
#define COMPOSER_FUNC_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

typedef struct Func Func;
typedef Func *func;

typedef double (*eval_func)(Func **args, int count, double delta, void *context);
typedef void (*init_func)(Func **args, int count, double delta, void *context);
typedef void (*free_func)(void *context);

struct Func
{
    Func **args;
    int count;
    size_t size;
    double delta;
    void *context;
    void *initial;
    init_func init;
    eval_func eval;
    free_func free;
};

Func *func_create_int(init_func init, eval_func eval, free_func free, size_t size, void *blank, int count)
{
    void *context = size > 0 ? calloc(1, size) : NULL;
    void *initial = size > 0 ? calloc(1, size) : NULL;
    if (blank != NULL)
    {
        memcpy(initial, blank, size);
    }
    Func **args = count > 0 ? (Func **)calloc(count, sizeof(Func *)) : NULL;
    Func *func = (Func *)calloc(1, sizeof(Func));
    *func = (Func){
        .args = args,
        .count = count,
        .size = size,
        .context = context,
        .initial = initial,
        .init = init,
        .eval = eval,
        .free = free,
    };
    return func;
}

Func *func_create_args(init_func init, eval_func eval, free_func free, size_t size, void *context, int count, Func **args)
{
    Func *func = func_create_int(init, eval, free, size, context, count);
    memcpy(func->args, args, count * sizeof(Func *));
    return func;
}

Func *func_create_va(init_func init, eval_func eval, free_func free, size_t size, void *context, int count, va_list valist)
{
    Func *func = func_create_int(init, eval, free, size, context, count);
    for (int i = 0; i < count; i++)
    {
        func->args[i] = va_arg(valist, Func *);
    }
    return func;
}

Func *func_create(init_func init, eval_func eval, free_func free, size_t size, void *context, int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(init, eval, free, size, context, count, valist);
    va_end(valist);
    return func;
}

void func_init(Func *func, double delta)
{
    func->delta = delta;
    for (int i = 0; i < func->count; i++)
    {
        func_init(func->args[i], delta);
    }
    if (func->initial != NULL)
    {
        memcpy(func->context, func->initial, func->size);
    }
    if (func->init != NULL)
    {
        func->init(func->args, func->count, delta, func->context);
    }
}

void func_free(Func *func)
{
    if (func->args != NULL)
    {
        Func **args = func->args;
        func->args = NULL;
        for (int i = 0; i < func->count; i++)
        {
            func_free(args[i]);
        }
        free(args);
    }
    if (func->context != NULL && func->free != NULL)
    {
        void *context = func->context;
        func->context = NULL;
        func->free(context);
        free(context);
    }
}

double func_eval(Func *func)
{
    return func->eval(func->args, func->count, func->delta, func->context);
}

#endif // COMPOSER_FUNC_H

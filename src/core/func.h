//
// func.h - An interface for creating and evaluating functions.
//
// This is the heart of the library.
//
#ifndef CSYNTH_FUNC_H
#define CSYNTH_FUNC_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

typedef struct Func Func;
typedef Func *func;
typedef struct Gen Gen;

typedef double (*eval_cb)(Gen **args, int count, double delta, void *context);
typedef void (*init_cb)(Gen **args, int count, double delta, void *context);
typedef void (*free_cb)(void *context);

// Represents a function (R -> Rn) that takes one or more inputs and outputs a single value.
struct Func
{
    Func **args;
    int count;
    size_t size;
    void *initial;
    init_cb init;
    eval_cb eval;
    free_cb free;
};

struct Gen
{
    Func *func;
    Gen **args;
    double delta;
    void *context;
    void *reset;
};

Func *func_create_int(init_cb init, eval_cb eval, free_cb free, size_t size, void *blank, int count)
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
    };
    return func;
}

Func *func_create_array(init_cb init, eval_cb eval, free_cb free, size_t size, void *context, int count, Func **args)
{
    Func *func = func_create_int(init, eval, free, size, context, count);
    memcpy(func->args, args, count * sizeof(Func *));
    return func;
}

Func *func_create_va(init_cb init, eval_cb eval, free_cb free, size_t size, void *context, int count, va_list valist)
{
    Func *func = func_create_int(init, eval, free, size, context, count);
    for (int i = 0; i < count; i++)
    {
        func->args[i] = va_arg(valist, Func *);
    }
    return func;
}

Func *func_create(init_cb init, eval_cb eval, free_cb free, size_t size, void *context, int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(init, eval, free, size, context, count, valist);
    va_end(valist);
    return func;
}

Gen *gen_create(Func *func, double delta)
{
    void *context = func->size > 0 ? calloc(1, func->size) : NULL;
    if (context != NULL && func->initial != NULL)
    {
        memcpy(context, func->initial, func->size);
    }
    void *reset = func->initial;
    if (func->init != NULL)
    {
        reset = func->size > 0 ? calloc(1, func->size) : NULL;
        if (reset != NULL && func->initial != NULL)
        {
            memcpy(reset, func->initial, func->size);
        }
    }
    Gen **args = func->count > 0 ? (Gen **)calloc(func->count, sizeof(Gen *)) : NULL;
    for (int i = 0; i < func->count; i++)
    {
        args[i] = gen_create(func->args[i], delta);
    }
    if (func->init != NULL)
    {
        func->init(args, func->count, delta, context);
        if (context != NULL && reset != NULL)
        {
            memcpy(reset, context, func->size);
        }
    }
    Gen *gen = (Gen *)calloc(1, sizeof(Gen));
    *gen = (Gen){
        .func = func,
        .args = args,
        .delta = delta,
        .context = context,
        .reset = reset,
    };
    return gen;
}

void gen_free(Gen *gen)
{
    Func *func = gen->func;
    if (func->free != NULL)
    {
        func->free(gen->context);
    }
    if (gen->args != NULL)
    {
        for (int i = 0; i < func->count; i++)
        {
            gen_free(gen->args[i]);
        }
        free(gen->args);
    }
    if (gen->context != NULL)
    {
        free(gen->context);
    }
    if (gen->reset != NULL && func->init != NULL)
    {
        free(gen->reset);
    }
    free(gen);
}

double gen_eval(Gen *gen)
{
    Func *func = gen->func;
    return func->eval(gen->args, func->count, gen->delta, gen->context);
}

void gen_reset(Gen *gen)
{
    Func *func = gen->func;
    for (int i = 0; i < func->count; i++)
    {
        gen_reset(gen->args[i]);
    }
    if (gen->context != NULL)
    {
        if (gen->reset != NULL)
        {
            memcpy(gen->context, gen->reset, func->size);
        }
        else
        {
            memset(gen->context, 0, func->size);
        }
    }
}

void test_func()
{
}

#endif // CSYNTH_FUNC_H

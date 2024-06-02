//
// gen.h - An interface for evaluating functions.
//
#ifndef CSYNTH_GEN_H
#define CSYNTH_GEN_H

#include <stdlib.h>
#include <string.h>

#include "./def.h"

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
        func->init(func->count, args, delta, context);
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
        func->free(func->count, gen->context);
    }
    if (gen->args != NULL)
    {
        for (int i = 0; i < func->count; i++)
        {
            gen_free(gen->args[i]);
        }
        free(gen->args);
    }
    free(gen->context);
    if (func->init != NULL)
    {
        free(gen->reset);
    }
    free(gen);
}

double gen_eval(Gen *gen)
{
    Func *func = gen->func;
    return func->eval(func->count, gen->args, gen->delta, gen->context);
}

void gen_reset(Gen *gen)
{
    Func *func = gen->func;
    if (func->flags & FUNC_FLAG_STOP_RESET)
    {
        return;
    }
    for (int i = 0; i < func->count; i++)
    {
        gen_reset(gen->args[i]);
    }
    if (func->flags & FUNC_FLAG_SKIP_RESET)
    {
        return;
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

#endif // CSYNTH_GEN_H

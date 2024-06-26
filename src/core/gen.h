//
// gen.h - An interface for evaluating functions.
//
#ifndef CSYNTH_GEN_H
#define CSYNTH_GEN_H

#include <string.h>

#include "../mem/alloc.h"
#include "../util/error.h"
#include "./def.h"

void gen_free(Gen *gen)
{
    Func *func = gen->func;
    if (func->free_cb != NULL)
    {
        func->free_cb(func->count, gen->context);
    }
    if (gen->args != NULL)
    {
        for (int i = 0; i < func->count; i++)
        {
            gen_free(gen->args[i]);
        }
        free_(gen->args);
    }
    free_(gen->context);
    if (func->init_cb != NULL)
    {
        free_(gen->reset);
    }
    free_(gen);
}

Gen *gen_create(Func *func)
{
    void *context = NULL;
    if (func->size > 0)
    {
        context = malloc_(func->size);
        if (context == NULL)
        {
            return error_null(csErrorMemoryAlloc);
        }
        if (func->initial != NULL)
        {
            memcpy(context, func->initial, func->size);
        }
        else
        {
            memset(context, 0, func->size);
        }
    }
    void *reset = func->initial;
    if (func->init_cb != NULL)
    {
        if (func->size > 0)
        {
            reset = malloc_(func->size);
            if (reset == NULL)
            {
                free_(context);
                return error_null(csErrorMemoryAlloc);
            }
            if (func->initial != NULL)
            {
                memcpy(reset, func->initial, func->size);
            }
            else
            {
                memset(reset, 0, func->size);
            }
        }
        else
        {
            reset = NULL;
        }
    }
    Gen **args = NULL;
    if (func->count > 0)
    {
        args = (Gen **)malloc_(func->count * sizeof(Gen *));
        if (args == NULL)
        {
            free_(context);
            free_(reset);
            return error_null(csErrorMemoryAlloc);
        }
    }
    for (int i = 0; i < func->count; i++)
    {
        Gen *arg = gen_create(func->args[i]);
        if (arg == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                gen_free(args[j]);
            }
            free_(args);
            free_(context);
            free_(reset);
            return NULL;
        }
        args[i] = arg;
    }
    if (func->init_cb != NULL)
    {
        func->init_cb(func->count, args, context);
        if (context != NULL && reset != NULL)
        {
            memcpy(reset, context, func->size);
        }
    }
    Gen *gen = (Gen *)malloc_(sizeof(Gen));
    if (gen == NULL)
    {
        free_(context);
        free_(reset);
        free_(args);
        return error_null(csErrorMemoryAlloc);
    }
    *gen = (Gen){
        .func = func,
        .args = args,
        .context = context,
        .reset = reset,
    };
    return gen;
}

double gen_eval(Gen *gen, Eval eval)
{
    Func *func = gen->func;
    return func->eval_cb(func->count, gen->args, eval, gen->context);
}

void gen_reset(Gen *gen)
{
    Func *func = gen->func;
    if (func->flags & FuncFlagStopReset)
    {
        return;
    }
    for (int i = 0; i < func->count; i++)
    {
        gen_reset(gen->args[i]);
    }
    if (func->flags & FuncFlagSkipReset)
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

Eval eval_create(double value)
{
    Eval eval = {0};
    for (EvalTick tick = 0; tick < EvalTickLength; tick++)
    {
        eval.tick[tick] = value;
    }
    return eval;
}

#endif // CSYNTH_GEN_H

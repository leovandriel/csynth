//
// comp.h - Sequential composition of functions.
//
// comp(...) takes multiple amplitude-duration pairs (both functions) and
// composes amplitudes sequentially, each with specified duration. This can be
// used for playing notes in sequence.
//
// Has two modes:
// - abs: Each duration is absolute, with each larger than the previous.
// - rel: Each duration is relative, specifying the duration of a single
//   function.
//
#ifndef CSYNTH_COMP_H
#define CSYNTH_COMP_H

#include <stdarg.h>

#include "../../core/func.h"

typedef struct
{
    double time;
    unsigned long index;
    unsigned long counter;
} CompContext;

static double comp_eval_abs(int count, Gen **args, double delta, void *context_)
{
    CompContext *context = (CompContext *)context_;
    double output = 0.0;
    for (int index = count / 2 - 1; index >= 0; index--)
    {
        double offset = gen_eval(args[index * 2]);
        if (context->time > offset)
        {
            output = gen_eval(args[index * 2 + 1]);
            break;
        }
    }
    context->time += delta;
    return output;
}

static double comp_eval_rel(int count, Gen **args, double delta, void *context_)
{
    CompContext *context = (CompContext *)context_;
    double offset = 0.0;
    double output = 0.0;
    for (int index = 0; index < count / 2; index++)
    {
        offset += gen_eval(args[index * 2 + 1]);
        if (context->time < offset)
        {
            output = gen_eval(args[index * 2]);
            break;
        }
    }
    context->time += delta;
    return output;
}

static double comp_eval_seq(int count, Gen **args, __attribute__((unused)) double delta, void *context_)
{
    CompContext *context = (CompContext *)context_;
    double output = gen_eval(args[context->index]);
    if (output < EPSILON && output > -EPSILON)
    {
        context->counter++;
    }
    else
    {
        context->counter = 0;
    }
    if (context->counter > 100 && (int)context->index < count - 1)
    {
        context->index++;
        context->counter = 0;
    }
    return output;
}

Func *comp_abs_args(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, comp_eval_abs, NULL, sizeof(CompContext), NULL, count, valist);
    va_end(valist);
    return func;
}

Func *comp_rel_args(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, comp_eval_rel, NULL, sizeof(CompContext), NULL, count, valist);
    va_end(valist);
    return func;
}

Func *comp_seq_args(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, comp_eval_seq, NULL, sizeof(CompContext), NULL, count, valist);
    va_end(valist);
    return func;
}

#define comp_abs(...) (comp_abs_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))
#define comp_rel(...) (comp_rel_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))
#define comp_seq(...) (comp_seq_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))

Func *comp_abs_array(int count, Func **args)
{
    return func_create_array(NULL, comp_eval_abs, NULL, sizeof(CompContext), NULL, count, args);
}

Func *comp_rel_array(int count, Func **args)
{
    return func_create_array(NULL, comp_eval_rel, NULL, sizeof(CompContext), NULL, count, args);
}

Func *comp_seq_array(int count, Func **args)
{
    return func_create_array(NULL, comp_eval_seq, NULL, sizeof(CompContext), NULL, count, args);
}

#endif // CSYNTH_COMP_H

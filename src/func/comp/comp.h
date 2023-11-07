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

#include <assert.h>
#include <math.h>
#include <stdarg.h>

#include "../../core/func.h"
#include "../gen/const.h"

typedef struct
{
    double time;
    unsigned long index;
    unsigned long counter;
} CompContext;

static double comp_eval_abs(Gen **args, int count, double delta, void *_context)
{
    CompContext *context = (CompContext *)_context;
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

static double comp_eval_rel(Gen **args, int count, double delta, void *_context)
{
    CompContext *context = (CompContext *)_context;
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

static const double COMP_EPSILON = 1e-9;

static double comp_eval_seq(Gen **args, int count, __attribute__((unused)) double delta, void *_context)
{
    CompContext *context = (CompContext *)_context;
    double output = gen_eval(args[context->index]);
    if (fabs(output) < COMP_EPSILON)
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

void test_comp()
{
    Func *t = comp_rel(const_(1), const_(0.2), const_(-1), const_(0.3));
    Gen *g = gen_create(t, 0.1);
    double epsilon = 1e-9;
    assert(fabs(gen_eval(g) - 1.0) < epsilon);
    assert(fabs(gen_eval(g) - 1.0) < epsilon);
    assert(fabs(gen_eval(g) - -1.0) < epsilon);
    assert(fabs(gen_eval(g) - -1.0) < epsilon);
    assert(fabs(gen_eval(g) - -1.0) < epsilon);
    assert(fabs(gen_eval(g) - 0.0) < epsilon);
    assert(fabs(gen_eval(g) - 0.0) < epsilon);
    assert(fabs(gen_eval(g) - 0.0) < epsilon);
    assert(fabs(gen_eval(g) - 0.0) < epsilon);
}

#endif // CSYNTH_COMP_H

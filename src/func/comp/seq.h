//
// seq.h - Sequential composition of functions.
//
// seq(...) takes multiple amplitude-duration pairs (both functions) and
// composes amplitudes sequentially, each with specified duration. This can be
// used for playing notes in sequence.
//
// Has two modes:
// - abs: Each duration is absolute, with each larger than the previous.
// - rel: Each duration is relative, specifying the duration of a single
//   function.
//
#ifndef CSYNTH_SEQ_H
#define CSYNTH_SEQ_H

#include <stdarg.h>

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    double time;
    unsigned long index;
    unsigned long counter;
} SeqContext;

static double seq_eval_abs(int count, Gen **args, double delta, void *context_)
{
    SeqContext *context = (SeqContext *)context_;
    double output = 0.0;
    // TODO: use context->index and track time per interval (allowing variable durations)
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

static double seq_eval_rel(int count, Gen **args, double delta, void *context_)
{
    SeqContext *context = (SeqContext *)context_;
    double offset = 0.0;
    double output = 0.0;
    // TODO: use context->index and track time per interval (allowing variable durations)
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

static double seq_eval_seq(int count, Gen **args, __attribute__((unused)) double delta, void *context_)
{
    SeqContext *context = (SeqContext *)context_;
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

static double seq_eval_fix(int count, Gen **args, double delta, void *context_)
{
    SeqContext *context = (SeqContext *)context_;
    double duration = gen_eval(args[0]);
    // TODO: use context->index and track time per interval (allowing variable duration)
    int index = (int)(context->time / duration) + 1;
    context->time += delta;
    return index < count ? gen_eval(args[index]) : 0;
}

Func *seq_abs_args(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, seq_eval_abs, NULL, sizeof(SeqContext), NULL, FUNC_FLAG_DEFAULT, count, valist);
    va_end(valist);
    return func;
}

Func *seq_rel_args(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, seq_eval_rel, NULL, sizeof(SeqContext), NULL, FUNC_FLAG_DEFAULT, count, valist);
    va_end(valist);
    return func;
}

Func *seq_seq_args(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, seq_eval_seq, NULL, sizeof(SeqContext), NULL, FUNC_FLAG_DEFAULT, count, valist);
    va_end(valist);
    return func;
}

Func *seq_fix_args(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, seq_eval_fix, NULL, sizeof(SeqContext), NULL, FUNC_FLAG_DEFAULT, count, valist);
    va_end(valist);
    return func;
}

#define seq_abs(...) (seq_abs_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))
#define seq_rel(...) (seq_rel_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))
#define seq_seq(...) (seq_seq_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))
#define seq_fix(...) (seq_fix_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))
#define seq_fix_(_duration, ...) (seq_fix_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)) + 1, const_(_duration), __VA_ARGS__))

Func *seq_abs_array(int count, Func **args)
{
    return func_create_array(NULL, seq_eval_abs, NULL, sizeof(SeqContext), NULL, FUNC_FLAG_DEFAULT, count, args);
}

Func *seq_rel_array(int count, Func **args)
{
    return func_create_array(NULL, seq_eval_rel, NULL, sizeof(SeqContext), NULL, FUNC_FLAG_DEFAULT, count, args);
}

Func *seq_seq_array(int count, Func **args)
{
    return func_create_array(NULL, seq_eval_seq, NULL, sizeof(SeqContext), NULL, FUNC_FLAG_DEFAULT, count, args);
}

Func *seq_fix_array(int count, Func **args)
{
    return func_create_array(NULL, seq_eval_fix, NULL, sizeof(SeqContext), NULL, FUNC_FLAG_DEFAULT, count, args);
}

#endif // CSYNTH_SEQ_H

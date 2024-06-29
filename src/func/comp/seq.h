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
    size_t index;
    size_t counter;
} SeqContext;

static double seq_eval_abs(int count, Gen **args, Eval eval, void *context_)
{
    SeqContext *context = (SeqContext *)context_;
    double output = 0.0;
    // TODO(leo): use context->index and track time per interval (allowing variable durations)
    for (int index = count / 2 - 1; index >= 0; index--)
    {
        double offset = gen_eval(args[index * 2], eval);
        if (context->time > offset)
        {
            output = gen_eval(args[index * 2 + 1], eval);
            break;
        }
    }
    context->time += eval.tick[EvalTickPitch];
    return output;
}

static double seq_eval_rel(int count, Gen **args, Eval eval, void *context_)
{
    SeqContext *context = (SeqContext *)context_;
    double offset = 0.0;
    double output = 0.0;
    // TODO(leo): use context->index and track time per interval (allowing variable durations)
    for (int index = 0; index < count / 2; index++)
    {
        offset += gen_eval(args[index * 2 + 1], eval);
        if (context->time < offset)
        {
            output = gen_eval(args[index * 2], eval);
            break;
        }
    }
    context->time += eval.tick[EvalTickPitch];
    return output;
}

static double seq_eval_seq(int count, Gen **args, Eval eval, void *context_)
{
    SeqContext *context = (SeqContext *)context_;
    double output = gen_eval(args[context->index], eval);
    if (output < FUNC_AUDIBLE && output > -FUNC_AUDIBLE)
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

static double seq_eval_fix(int count, Gen **args, Eval eval, void *context_)
{
    SeqContext *context = (SeqContext *)context_;
    double duration = gen_eval(args[0], eval);
    // TODO(leo): use context->index and track time per interval (allowing variable duration)
    int index = (int)(context->time / duration) + 1;
    context->time += eval.tick[EvalTickPitch];
    return index < count ? gen_eval(args[index], eval) : 0;
}

Func *seq_abs_array(int count, Func **args)
{
    return func_create(NULL, seq_eval_abs, NULL, sizeof(SeqContext), NULL, FuncFlagNone, count, args);
}

Func *seq_rel_array(int count, Func **args)
{
    return func_create(NULL, seq_eval_rel, NULL, sizeof(SeqContext), NULL, FuncFlagNone, count, args);
}

Func *seq_seq_array(int count, Func **args)
{
    return func_create(NULL, seq_eval_seq, NULL, sizeof(SeqContext), NULL, FuncFlagNone, count, args);
}

Func *seq_fix_array(int count, Func **args)
{
    return func_create(NULL, seq_eval_fix, NULL, sizeof(SeqContext), NULL, FuncFlagNone, count, args);
}

#define seq_abs(...) (seq_abs_array(FUNCS(__VA_ARGS__)))
#define seq_rel(...) (seq_rel_array(FUNCS(__VA_ARGS__)))
#define seq_seq(...) (seq_seq_array(FUNCS(__VA_ARGS__)))
#define seq_fix(...) (seq_fix_array(FUNCS(__VA_ARGS__)))
#define seq_fix_(_duration, ...) (seq_fix_array(FUNCS(const_(_duration), __VA_ARGS__)))

#endif // CSYNTH_SEQ_H

#ifndef CSYNTH_SEQ_H
#define CSYNTH_SEQ_H

#include "../../core/func.h"
#include "../../core/gen.h"

#define SEQ_SILENT_SAMPLE_COUNT 10

/** @see seq_create */
typedef struct
{
    /** @brief Total elapsed. */
    double time;
    /** @brief Index of the current function. */
    size_t index;
    /** @brief Counter for silence detection. */
    size_t counter;
} SeqContext;

static double seq_eval_abs(size_t count, Gen **args, Eval *eval, void *context_)
{
    SeqContext *context = (SeqContext *)context_;
    double tick = gen_eval(args[0], eval);
    double output = 0.0;
    // TODO(leo): use context->index and track time per interval (allowing
    // variable durations)
    for (size_t index = count / 2; index > 0; index--)
    {
        double offset = gen_eval(args[index * 2 - 1], eval);
        if (context->time >= offset)
        {
            output = gen_eval(args[index * 2], eval);
            break;
        }
    }
    context->time += tick;
    return output;
}

/**
 * @brief Sequential composition of functions.
 *
 * Takes multiple time-input pairs (both functions) and composes these
 * sequentially, each input starting a given time.
 *
 * @param count Number of function arguments, i.e. 2x the number of inputs.
 * @param args Array of function arguments
 * @return Func* Sequence function.
 */
Func *seq_abs_create(size_t count, Func **args)
{
    return func_create_args(NULL, seq_eval_abs, NULL, sizeof(SeqContext), NULL, FuncFlagNone, count, args, "tick, input");
}

static double seq_eval_rel(size_t count, Gen **args, Eval *eval, void *context_)
{
    SeqContext *context = (SeqContext *)context_;
    double tick = gen_eval(args[0], eval);
    double offset = 0.0;
    double output = 0.0;
    // TODO(leo): use context->index and track time per interval (allowing
    // variable durations)
    for (size_t index = 0; index < count / 2; index++)
    {
        offset += gen_eval(args[index * 2 + 2], eval);
        if (context->time < offset)
        {
            output = gen_eval(args[index * 2 + 1], eval);
            break;
        }
    }
    context->time += tick;
    return output;
}

/**
 * @brief Sequential composition of functions.
 *
 * Takes multiple input-duration pairs (both functions) and composes these
 * sequentially, each input having given duration.
 *
 * @param count Number of function arguments, i.e. 2x the number of inputs.
 * @param args Array of function arguments
 * @return Func* Sequence function.
 */
Func *seq_rel_create(size_t count, Func **args)
{
    return func_create_args(NULL, seq_eval_rel, NULL, sizeof(SeqContext), NULL, FuncFlagNone, count, args, "tick, input");
}

static double seq_eval_seq(size_t count, Gen **args, Eval *eval, void *context_)
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
    if (context->counter >= SEQ_SILENT_SAMPLE_COUNT && context->index < count - 1)
    {
        context->index++;
        context->counter = 0;
    }
    return output;
}

/**
 * @brief Sequential composition of functions.
 *
 * Takes multiple input functions and composes these sequentially, each sampled
 * until silent for SEQ_SILENT_SAMPLE_COUNT samples.
 *
 * @param count Number of function arguments, i.e. the number of inputs.
 * @param args Array of function arguments
 * @return Func* Seq function
 */
Func *seq_seq_create(size_t count, Func **args)
{
    return func_create_args(NULL, seq_eval_seq, NULL, sizeof(SeqContext), NULL, FuncFlagNone, count, args, "input");
}

static double seq_eval_fix(size_t count, Gen **args, Eval *eval, void *context_)
{
    SeqContext *context = (SeqContext *)context_;
    double tick = gen_eval(args[0], eval);
    size_t index = (size_t)context->time + 1;
    context->time += tick;
    return index < count ? gen_eval(args[index], eval) : 0;
}

/**
 * @brief Sequential composition of functions.
 *
 * Takes periods-per-sample (tick) and multiple input functions and composes
 * these sequentially, each sampled for a fixed duration.
 *
 * @param count Number of function arguments, i.e. 2x+1 the number of inputs.
 * @param args Array of function arguments
 * @return Func* Seq function
 */
Func *seq_fix_create(size_t count, Func **args)
{
    return func_create_args(NULL, seq_eval_fix, NULL, sizeof(SeqContext), NULL, FuncFlagNone, count, args, "tick, input");
}

#endif // CSYNTH_SEQ_H

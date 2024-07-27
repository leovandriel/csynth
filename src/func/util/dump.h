#ifndef CSYNTH_DUMP_H
#define CSYNTH_DUMP_H

#include <stdio.h>

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see dump_create */
typedef struct
{
    /** @brief Last output value. */
    double output;
    /** @brief Last direction. */
    int dir;
    /** @brief Index of the last zero crossing. */
    long min;
    /** @brief Index of the last zero crossing. */
    long max;
    /** @brief Index of the last zero crossing. */
    long zero0;
    /** @brief Index of the last zero crossing. */
    long zero1;
    /** @brief Number of samples to log. */
    size_t count;
    /** @brief Number of samples to skip. */
    size_t step;
    /** @brief Current index. */
    size_t index;
} DumpContext;

static double dump_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    DumpContext *context = (DumpContext *)context_;
    double input = gen_eval(args[0], eval);
    int dir_up = context->index > 0 && context->output < input;
    int dir_down = context->index > 0 && context->output > input;
    int dir = dir_up ? '/' : (dir_down ? '\\' : (context->index > 0 ? '-' : '.'));
    int at_zero = context->index > 0 && (context->output > 0) != (input > 0);
    int at_min = context->index > 1 && dir != context->dir && dir == '/';
    int at_max = context->index > 1 && dir != context->dir && dir == '\\';
    double diff = input - context->output;
    double frequency = -1.0;
    if (at_zero)
    {
        if (context->zero1 != -1)
        {
            frequency = 1.0 / (diff * (double)(context->index - context->zero1));
        }
        context->zero1 = context->zero0;
        context->zero0 = (long)context->index;
    }
    else if (at_min)
    {
        if (context->min != -1)
        {
            frequency = 1.0 / (diff * (double)(context->index - context->min));
        }
        context->min = (long)context->index;
    }
    else if (at_max)
    {
        if (context->max != -1)
        {
            frequency = 1.0 / (diff * (double)(context->index - context->max));
        }
        context->max = (long)context->index;
    }
    if (context->index < context->count * context->step && context->index % context->step == 0)
    {
        const char *pass = at_zero ? "zero" : (at_min ? "min" : (at_max ? "max" : ""));
        char buffer[100];
        snprintf(buffer, 100, "%f", frequency);
        const char *freq = frequency >= 0 ? buffer : "";
        fprintf(stderr, "index: %lu  value: %f  diff: %f  dir: %c %s %s\n", context->index, input, diff, dir, pass, freq);
    }
    context->dir = dir;
    context->output = input;
    context->index++;
    return input;
}

/**
 * @brief Create a function that logs the samples plus some metrics.
 *
 * @param count Number of samples to log.
 * @param step Number of samples to skip.
 * @param input Input signal.
 * @return Func* Dump function.
 */
Func *dump_create(size_t count, size_t step, Func *input)
{
    DumpContext initial = {
        .min = -1,
        .max = -1,
        .zero0 = -1,
        .zero1 = -1,
        .count = count,
        .step = step,
    };
    return func_create(NULL, dump_eval, NULL, sizeof(DumpContext), &initial, FuncFlagNone, input);
}

#endif // CSYNTH_DUMP_H

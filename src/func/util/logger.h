//
// logger.h - Logs the samples plus some metrics
//
// `logger(input, count)` with count the maximum number of log to be logged.
//
#ifndef CSYNTH_LOGGER_H
#define CSYNTH_LOGGER_H

#include <assert.h>
#include <stdio.h>

#include "../../core/func.h"

typedef struct
{
    double output;
    char dir;
    long min;
    long max;
    long zero0;
    long zero1;
    unsigned long count;
    unsigned long step;
    unsigned long index;
} LoggerContext;

static double logger_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    LoggerContext *context = (LoggerContext *)_context;
    double input = gen_eval(args[0]);
    int dir_up = context->index > 0 && context->output < input;
    int dir_down = context->index > 0 && context->output > input;
    char dir = dir_up ? '/' : dir_down         ? '\\'
                          : context->index > 0 ? '-'
                                               : '.';
    int at_zero = context->index > 0 && (context->output > 0) != (input > 0);
    int at_min = context->index > 1 && dir != context->dir && dir == '/';
    int at_max = context->index > 1 && dir != context->dir && dir == '\\';
    double diff = input - context->output;
    double frequency = -1.0;
    if (at_zero)
    {
        if (context->zero1 != -1)
        {
            frequency = 1.0 / (diff * (context->index - context->zero1));
        }
        context->zero1 = context->zero0;
        context->zero0 = context->index;
    }
    else if (at_min)
    {
        if (context->min != -1)
        {
            frequency = 1.0 / (diff * (context->index - context->min));
        }
        context->min = context->index;
    }
    else if (at_max)
    {
        if (context->max != -1)
        {
            frequency = 1.0 / (diff * (context->index - context->max));
        }
        context->max = context->index;
    }
    if (context->index < context->count * context->step && context->index % context->step == 0)
    {
        const char *pass = at_zero ? "zero" : at_min ? "min"
                                          : at_max   ? "max"
                                                     : "";
        double time = context->index * delta;
        char buffer[100];
        snprintf(buffer, 100, "%f", frequency);
        const char *freq = frequency >= 0 ? buffer : "";
        fprintf(stderr, "index: %lu  time: %f  value: %f  diff: %f  dir: %c %s %s\n", context->index, time, input, diff, dir, pass, freq);
    }
    context->dir = dir;
    context->output = input;
    context->index += 1;
    return input;
}

Func *logger(Func *input, unsigned long count, unsigned long step)
{
    LoggerContext initial = (LoggerContext){
        .min = -1,
        .max = -1,
        .zero0 = -1,
        .zero1 = -1,
        .count = count,
        .step = step,
    };
    return func_create(NULL, logger_eval, NULL, sizeof(LoggerContext), &initial, 1, input);
}

Func *log20(Func *input)
{
    return logger(input, 20, 1);
}

Func *log1k(Func *input)
{
    return logger(input, 1000, 1);
}

Func *log10sec(Func *input)
{
    return logger(input, 10, 4410);
}

void test_logger()
{
}

#endif // CSYNTH_LOGGER_H

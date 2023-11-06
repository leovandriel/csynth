//
// logger.h - Logs the samples plus some metrics
//
// `logger(input, count)` with count the maximum number of log to be logged.
//
#ifndef COMPOSER_LOGGER_H
#define COMPOSER_LOGGER_H

#include <assert.h>
#include <stdio.h>

#include "../core/func.h"

typedef struct
{
    double output;
    char dir;
    long min;
    long max;
    long zero0;
    long zero1;
    unsigned long count;
    unsigned long index;
} LoggerContext;

double logger_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    LoggerContext *context = (LoggerContext *)_context;
    double input = gen_eval(args[0]);
    if (context->index < context->count)
    {
        int dir_up = context->index > 0 && context->output < input;
        int dir_down = context->index > 0 && context->output > input;
        char dir = dir_up ? '/' : dir_down         ? '\\'
                              : context->index > 0 ? '-'
                                                   : '.';
        int at_zero = context->index > 0 && (context->output > 0) != (input > 0);
        int at_min = context->index > 1 && dir != context->dir && dir == '/';
        int at_max = context->index > 1 && dir != context->dir && dir == '\\';
        const char *pass = at_zero ? "zero" : at_min ? "min"
                                          : at_max   ? "max"
                                                     : "";
        double time = context->index * delta;
        double delta = input - context->output;
        double frequency = -1.0;
        if (at_zero)
        {
            if (context->zero1 != -1)
            {
                frequency = 1.0 / (delta * (context->index - context->zero1));
            }
            context->zero1 = context->zero0;
            context->zero0 = context->index;
        }
        else if (at_min)
        {
            if (context->min != -1)
            {
                frequency = 1.0 / (delta * (context->index - context->min));
            }
            context->min = context->index;
        }
        else if (at_max)
        {
            if (context->max != -1)
            {
                frequency = 1.0 / (delta * (context->index - context->max));
            }
            context->max = context->index;
        }
        char buffer[100];
        snprintf(buffer, 100, "%f", frequency);
        const char *freq = frequency >= 0 ? buffer : "";
        fprintf(stderr, "index: %lu  time: %f  value: %f  delta: %f  dir: %c %s %s\n", context->index, time, input, delta, dir, pass, freq);
        context->dir = dir;
        context->output = input;
        context->index += 1;
        return 0.0;
    }
    context->index += 1;
    return input;
}

Func *logger(Func *input, unsigned long count)
{
    LoggerContext initial = (LoggerContext){
        .min = -1,
        .max = -1,
        .zero0 = -1,
        .zero1 = -1,
        .count = count,
    };
    return func_create(NULL, logger_eval, NULL, sizeof(LoggerContext), &initial, 1, input);
}

Func *log1k(Func *input)
{
    return logger(input, 1000);
}

void test_logger()
{
}

#endif // COMPOSER_LOGGER_H

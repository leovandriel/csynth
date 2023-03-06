#ifndef COMPOSER_LOGGER_H
#define COMPOSER_LOGGER_H

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
} LoggerContext;

double logger_eval(unsigned long index, int rate, Func **args, __attribute__((unused)) int count, void *_context)
{
    LoggerContext *context = (LoggerContext *)_context;
    double input = func_eval(args[0], index, rate);
    if (index < context->count)
    {
        int dir_up = index > 0 && context->output < input;
        int dir_down = index > 0 && context->output > input;
        char dir = dir_up ? '/' : dir_down ? '\\'
                              : index > 0  ? '-'
                                           : '.';
        int at_zero = index > 0 && (context->output > 0) != (input > 0);
        int at_min = index > 1 && dir != context->dir && dir == '/';
        int at_max = index > 1 && dir != context->dir && dir == '\\';
        const char *pass = at_zero ? "zero" : at_min ? "min"
                                          : at_max   ? "max"
                                                     : "";
        double time = (double)index / rate;
        double delta = input - context->output;
        double frequency = -1.0;
        if (at_zero)
        {
            if (context->zero1 != -1)
            {
                frequency = (double)rate / (index - context->zero1);
            }
            context->zero1 = context->zero0;
            context->zero0 = index;
        }
        else if (at_min)
        {
            if (context->min != -1)
            {
                frequency = (double)rate / (index - context->min);
            }
            context->min = index;
        }
        else if (at_max)
        {
            if (context->max != -1)
            {
                frequency = (double)rate / (index - context->max);
            }
            context->max = index;
        }
        char buffer[100];
        snprintf(buffer, 100, "%f", frequency);
        const char *freq = frequency >= 0 ? buffer : "";
        printf("index: %lu  time: %f  value: %f  delta: %f  dir: %c %s %s\n", index, time, input, delta, dir, pass, freq);
        context->dir = dir;
        context->output = input;
        index++;
        return 0.0;
    }
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

#endif // COMPOSER_LOGGER_H

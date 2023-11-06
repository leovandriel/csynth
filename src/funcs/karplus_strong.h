//
// karplus_strong.h - Karplus-Strong algorithm
//
// `karplus_strong(frequency, decay)`
//
#ifndef CSYNTH_KARPLUS_STRONG_H
#define CSYNTH_KARPLUS_STRONG_H

#include <assert.h>
#include <math.h>

#include "../core/func.h"
#include "./cons.h"

typedef struct
{
    double *buffer;
    unsigned long size;
    unsigned long index;
    unsigned long max;
} KarplusStrongContext;

double karplus_strong_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    KarplusStrongContext *context = (KarplusStrongContext *)_context;
    double frequency = gen_eval(args[0]);
    unsigned long size = round(1.0 / (delta * frequency));
    double decay = pow(gen_eval(args[1]), 1.0 / size);
    if (size != context->size)
    {
        if (context->buffer == NULL)
        {
            context->buffer = (double *)calloc(size, sizeof(double));
            for (unsigned long i = 0; i < size; i++)
            {
                context->buffer[i] = 2.0 * rand() / RAND_MAX - 1.0;
            }
            context->max = size;
        }
        else if (size > context->max)
        {
            unsigned long max = size * 2;
            context->buffer = (double *)realloc(context->buffer, max * sizeof(double));
            memset(context->buffer + context->max, 0, (max - context->max) * sizeof(double));
            // TODO: shift the contents of the buffer
            context->max = max;
        }
        context->size = size;
    }
    unsigned long next = (context->index + 1) % size;
    context->buffer[context->index] = 0.5 * (context->buffer[context->index] + context->buffer[next]) * decay;
    double output = context->buffer[context->index];
    context->index = next;
    return output;
}

void karplus_strong_free(void *_context)
{
    KarplusStrongContext *context = (KarplusStrongContext *)_context;
    if (context->buffer != NULL)
    {
        free(context->buffer);
    }
}

Func *karplus_strong(Func *frequency, Func *decay)
{
    return func_create(NULL, karplus_strong_eval, karplus_strong_free, sizeof(KarplusStrongContext), NULL, 2, frequency, decay);
}

#define karplus_strong_(_frequency, _decay) (karplus_strong(cons(_frequency), cons(_decay)))

void test_karplus_strong()
{
    srand(0);
    func t = karplus_strong(cons(2), cons(0.5));
    Gen *g = gen_create(t, 0.1);
    double epsilon = 1e-4;
    assert(fabs(gen_eval(g) - -0.647648) < epsilon);
    assert(fabs(gen_eval(g) - -0.525283) < epsilon);
    assert(fabs(gen_eval(g) - -0.176033) < epsilon);
    assert(fabs(gen_eval(g) - -0.450578) < epsilon);
    assert(fabs(gen_eval(g) - -0.658184) < epsilon);
    assert(fabs(gen_eval(g) - -0.510548) < epsilon);
    assert(fabs(gen_eval(g) - -0.305265) < epsilon);
    assert(fabs(gen_eval(g) - -0.272748) < epsilon);
    assert(fabs(gen_eval(g) - -0.482617) < epsilon);
    assert(fabs(gen_eval(g) - -0.508720) < epsilon);
    assert(fabs(gen_eval(g) - -0.355103) < epsilon);
    assert(fabs(gen_eval(g) - -0.251595) < epsilon);
}

#endif // CSYNTH_KARPLUS_STRONG_H

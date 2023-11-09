//
// karplus_strong.h - Karplus-Strong algorithm
//
// `karplus_strong(frequency, decay)`
//
#ifndef CSYNTH_KARPLUS_STRONG_H
#define CSYNTH_KARPLUS_STRONG_H

#include <assert.h>
#include <math.h>

#include "../../core/func.h"
#include "../../util/buffer.h"
#include "../gen/const.h"

typedef struct
{
    Buffer buffer;
    unsigned long index;
} KarplusStrongContext;

static double karplus_strong_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    KarplusStrongContext *context = (KarplusStrongContext *)context_;
    double frequency = gen_eval(args[0]);
    unsigned long size = round(1.0 / (delta * frequency));
    double decay = pow(gen_eval(args[1]), 1.0 / size);
    context->index = buffer_resize(&context->buffer, size, context->index, fill_rand_1_1);
    unsigned long next = (context->index + 1) % size;
    double *buffer = context->buffer.samples;
    buffer[context->index] = 0.5 * (buffer[context->index] + buffer[next]) * decay;
    double output = buffer[context->index];
    context->index = next;
    return output;
}

void karplus_strong_free(void *context_)
{
    KarplusStrongContext *context = (KarplusStrongContext *)context_;
    buffer_free(&context->buffer);
}

Func *karplus_strong(Func *frequency, Func *decay)
{
    return func_create(NULL, karplus_strong_eval, karplus_strong_free, sizeof(KarplusStrongContext), NULL, 2, frequency, decay);
}

Func *karplus_strong_(double frequency, double decay) { return karplus_strong(const_(frequency), const_(decay)); }

void test_karplus_strong()
{
    rand_seed(0);
    Func *t = karplus_strong(const_(2), const_(0.5));
    Gen *g = gen_create(t, 0.1);
    double epsilon = 1e-4;
    assert(fabs(gen_eval(g) - -0.288641) < epsilon);
    assert(fabs(gen_eval(g) - 0.491219) < epsilon);
    assert(fabs(gen_eval(g) - 0.419562) < epsilon);
    assert(fabs(gen_eval(g) - 0.424176) < epsilon);
    assert(fabs(gen_eval(g) - 0.277973) < epsilon);
    assert(fabs(gen_eval(g) - 0.088177) < epsilon);
    assert(fabs(gen_eval(g) - 0.396440) < epsilon);
    assert(fabs(gen_eval(g) - 0.367258) < epsilon);
    assert(fabs(gen_eval(g) - 0.305628) < epsilon);
    assert(fabs(gen_eval(g) - 0.159376) < epsilon);
    assert(fabs(gen_eval(g) - 0.210942) < epsilon);
    assert(fabs(gen_eval(g) - 0.332419) < epsilon);
}

#endif // CSYNTH_KARPLUS_STRONG_H

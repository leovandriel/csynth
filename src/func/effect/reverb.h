//
// reverb.h - Reverb function
//
// `reverb(input, interval, decay)` returns a reverberated version of input.
//
#ifndef CSYNTH_REVERB_H
#define CSYNTH_REVERB_H

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "../../core/func.h"
#include "../gen/const.h"
#include "../util/buffer.h"

typedef struct
{
    Buffer buffer;
    unsigned long index;
} ReverbContext;

static double reverb_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    ReverbContext *context = (ReverbContext *)_context;
    double input = gen_eval(args[0]);
    unsigned long size = round(gen_eval(args[1]) / delta);
    double decay = gen_eval(args[2]);
    context->index = buffer_resize(&context->buffer, size, context->index, NULL);
    double *buffer = context->buffer.samples;
    double output = buffer[context->index];
    buffer[context->index] = buffer[context->index] * decay + input;
    context->index = (context->index + 1) % size;
    return output;
}

static void reverb_free(void *_context)
{
    ReverbContext *context = (ReverbContext *)_context;
    buffer_free(&context->buffer);
}

Func *reverb(Func *input, Func *interval, Func *decay)
{
    return func_create(NULL, reverb_eval, reverb_free, sizeof(ReverbContext), NULL, 3, input, interval, decay);
}

Func *reverb_(Func *input, double interval, double decay) { return reverb(input, const_(interval), const_(decay)); }

void test_reverb()
{
    Func *t = reverb(const_(1), const_(.2), const_(.5));
    Gen *g = gen_create(t, 0.1);
    double epsilon = 1e-4;
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.500000) < epsilon);
    assert(fabs(gen_eval(g) - 1.500000) < epsilon);
    assert(fabs(gen_eval(g) - 1.750000) < epsilon);
    assert(fabs(gen_eval(g) - 1.750000) < epsilon);
    assert(fabs(gen_eval(g) - 1.875000) < epsilon);
    assert(fabs(gen_eval(g) - 1.875000) < epsilon);
    assert(fabs(gen_eval(g) - 1.937500) < epsilon);
    assert(fabs(gen_eval(g) - 1.937500) < epsilon);
}

#endif // CSYNTH_REVERB_H

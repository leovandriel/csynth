//
// reverb.h - Reverb function
//
// `reverb(input, interval, decay)` returns a reverberated version of input.
//
#ifndef CSYNTH_REVERB_H
#define CSYNTH_REVERB_H

#include <stdlib.h>
#include <string.h>

#include "../../util/test.h"
#include "../../core/func.h"
#include "../../util/buffer.h"
#include "../gen/const.h"

typedef struct
{
    Buffer buffer;
    unsigned long index;
} ReverbContext;

static double reverb_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    ReverbContext *context = (ReverbContext *)context_;
    double input = gen_eval(args[0]);
    unsigned long size = (unsigned long)(gen_eval(args[1]) / delta + 0.5);
    double decay = gen_eval(args[2]);
    context->index = buffer_resize(&context->buffer, size, context->index, NULL);
    double *buffer = context->buffer.samples;
    double output = buffer[context->index];
    buffer[context->index] = buffer[context->index] * decay + input;
    context->index = (context->index + 1) % size;
    return output;
}

static void reverb_free(void *context_)
{
    ReverbContext *context = (ReverbContext *)context_;
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
    assert_gen_equal(g, 0.00000);
    assert_gen_equal(g, 0.00000);
    assert_gen_equal(g, 1.00000);
    assert_gen_equal(g, 1.00000);
    assert_gen_equal(g, 1.50000);
    assert_gen_equal(g, 1.50000);
    assert_gen_equal(g, 1.75000);
    assert_gen_equal(g, 1.75000);
    assert_gen_equal(g, 1.87500);
    assert_gen_equal(g, 1.87500);
    assert_gen_equal(g, 1.93750);
    assert_gen_equal(g, 1.93750);
}

#endif // CSYNTH_REVERB_H

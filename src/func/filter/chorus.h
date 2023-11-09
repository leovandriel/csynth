//
// chorus.h - Chorus effect
//
// `chorus(input, modulation, delay, depth)`
// - `input` - Input signal
// - `modulation` - Modulation signal, typically a sine wave
// - `delay` - Delay time in seconds, typically 20ms
// - `depth` - Modulation depth in seconds, typically 3ms
//
#ifndef CSYNTH_CHORUS_H
#define CSYNTH_CHORUS_H

#include "../../util/test.h"
#include "../../core/func.h"
#include "../../util/buffer.h"
#include "../gen/const.h"
#include "../gen/sine.h"

typedef struct
{
    Buffer buffer;
    // unsigned long index;

    unsigned long index;
} ChorusContext;

static double chorus_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    ChorusContext *context = (ChorusContext *)context_;
    double input = gen_eval(args[0]);
    double modulation = gen_eval(args[1]);
    double delay = gen_eval(args[2]);
    double depth = gen_eval(args[3]);
    unsigned long size = (unsigned long)(delay / delta + 0.5);
    unsigned long offset = (unsigned long)(depth / delta * modulation + size * 0.5 + 0.5);
    // unsigned long offset = (unsigned long)(depth / delta * (modulation + 1) * 0.5 + 0.5);
    unsigned long index = (context->index + size - offset) % size;
    context->index = buffer_resize(&context->buffer, size, context->index, NULL);
    double *buffer = context->buffer.samples;
    double output = 0.5 * (input + buffer[index]);
    buffer[context->index] = input;
    context->index = (context->index + 1) % size;
    return output;
}

static void chorus_free(void *context_)
{
    ChorusContext *context = (ChorusContext *)context_;
    buffer_free(&context->buffer);
}

Func *chorus(Func *input, Func *modulation, Func *delay, Func *depth)
{
    return func_create(NULL, chorus_eval, chorus_free, sizeof(ChorusContext), NULL, 4, input, modulation, delay, depth);
}

Func *chorus_(Func *input, Func *modulation, double delay, double depth) { return chorus(input, modulation, const_(delay), const_(depth)); }

void test_chorus()
{
    Func *t = chorus_(sine_(10), sine_(.2), 0.2, 0.2);
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
}

#endif // CSYNTH_CHORUS_H

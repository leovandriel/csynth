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

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../mem/buffer.h"
#include "../gen/const.h"

typedef struct
{
    Buffer buffer;
    size_t index;
} ChorusContext;

static double chorus_eval(__U int count, Gen **args, Eval eval, void *context_)
{
    ChorusContext *context = (ChorusContext *)context_;
    double input = gen_eval(args[0], eval);
    double modulation = gen_eval(args[1], eval);
    double delay = gen_eval(args[2], eval);
    double depth = gen_eval(args[3], eval);
    size_t size = (size_t)(delay / eval.delta + 0.5);
    size_t offset = (size_t)(depth / eval.delta * modulation + (double)size * 0.5 + 0.5);
    // size_t offset = (size_t)(depth / eval.delta * (modulation + 1) * 0.5 + 0.5);
    size_t index = (context->index + size - offset) % size;
    context->index = buffer_resize(&context->buffer, size, context->index, NULL);
    double *buffer = context->buffer.samples;
    double output = 0.5 * (input + buffer[index]);
    buffer[context->index] = input;
    context->index = (context->index + 1) % size;
    return output;
}

static void chorus_free(__U int count, void *context_)
{
    ChorusContext *context = (ChorusContext *)context_;
    buffer_free(&context->buffer);
}

Func *chorus(Func *input, Func *modulation, Func *delay, Func *depth)
{
    return func_create(NULL, chorus_eval, chorus_free, sizeof(ChorusContext), NULL, FuncFlagNone, 4, input, modulation, delay, depth);
}

Func *chorus_(Func *input, Func *modulation, double delay, double depth) { return chorus(input, modulation, const_(delay), const_(depth)); }

#endif // CSYNTH_CHORUS_H

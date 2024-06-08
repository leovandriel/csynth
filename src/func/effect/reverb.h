//
// reverb.h - Reverb function
//
// `reverb(input, interval, decay)` returns a reverberated input.
//
#ifndef CSYNTH_REVERB_H
#define CSYNTH_REVERB_H

#include <stdlib.h>
#include <string.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../mem/buffer.h"
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
    double output = 0;
    if (buffer)
    {
        output = buffer[context->index];
        buffer[context->index] = buffer[context->index] * decay + input;
    }
    context->index = (context->index + 1) % size;
    return output;
}

static void reverb_free(__attribute__((unused)) int count, void *context_)
{
    ReverbContext *context = (ReverbContext *)context_;
    buffer_free(&context->buffer);
}

Func *reverb(Func *input, Func *interval, Func *decay)
{
    return func_create(NULL, reverb_eval, reverb_free, sizeof(ReverbContext), NULL, FUNC_FLAG_DEFAULT, 3, input, interval, decay);
}

Func *reverb_(Func *input, double interval, double decay) { return reverb(input, const_(interval), const_(decay)); }

#endif // CSYNTH_REVERB_H

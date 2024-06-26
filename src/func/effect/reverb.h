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

typedef struct
{
    Buffer buffer;
    size_t index;
} ReverbContext;

static double reverb_eval(__U int count, Gen **args, Eval eval, void *context_)
{
    ReverbContext *context = (ReverbContext *)context_;
    double tick = gen_eval(args[0], eval);
    double decay = gen_eval(args[1], eval);
    double input = gen_eval(args[2], eval);
    size_t size = (size_t)(1.0 / tick + 0.5);
    context->index = buffer_resize(&context->buffer, size, context->index, NULL);
    double *buffer = context->buffer.samples;
    double output = input;
    if (buffer != NULL)
    {
        buffer[context->index] = buffer[context->index] * decay + input;
        output = buffer[context->index];
        context->index = (context->index + 1) % size;
    }
    return output;
}

static void reverb_free(__U int count, void *context_)
{
    ReverbContext *context = (ReverbContext *)context_;
    buffer_free(&context->buffer);
}

Func *reverb_create(Func *tick, Func *decay, Func *input)
{
    return func_create(NULL, reverb_eval, reverb_free, sizeof(ReverbContext), NULL, FuncFlagNone, FUNCS(tick, decay, input));
}

#endif // CSYNTH_REVERB_H

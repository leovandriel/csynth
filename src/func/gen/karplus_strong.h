//
// karplus_strong.h - Karplus-Strong algorithm
//
// `karplus_strong(frequency, decay)`
//
#ifndef CSYNTH_KARPLUS_STRONG_H
#define CSYNTH_KARPLUS_STRONG_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../mem/buffer.h"
#include "./const.h"

typedef struct
{
    Buffer buffer;
    size_t index;
} KarplusStrongContext;

static double karplus_strong_eval(__U int count, Gen **args, Eval eval, void *context_)
{
    KarplusStrongContext *context = (KarplusStrongContext *)context_;
    double decay = gen_eval(args[0], eval);
    size_t size = (size_t)(1.0 / eval.audio_step + 0.5);
    context->index = buffer_resize(&context->buffer, size, context->index, fill_rand_1_1);
    size_t next = (context->index + 1) % size;
    double *buffer = context->buffer.samples;
    buffer[context->index] = 0.5 * (buffer[context->index] + buffer[next]) * pow(decay, eval.audio_step);
    double output = buffer[context->index];
    context->index = next;
    return output;
}

static void karplus_strong_free(__U int count, void *context_)
{
    KarplusStrongContext *context = (KarplusStrongContext *)context_;
    buffer_free(&context->buffer);
}

Func *karplus_strong_osc(Func *decay)
{
    return func_create(NULL, karplus_strong_eval, karplus_strong_free, sizeof(KarplusStrongContext), NULL, FuncFlagNone, 1, decay);
}

#endif // CSYNTH_KARPLUS_STRONG_H

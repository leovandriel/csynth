#ifndef CSYNTH_KARPLUS_STRONG_H
#define CSYNTH_KARPLUS_STRONG_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../mem/buffer.h"
#include "../../mem/fill.h"

/** @see karplus_strong_create */
typedef struct
{
    /** @brief Buffer to store the string samples. */
    Buffer buffer;
    /** @brief Index of the next sample to write. */
    size_t index;
    /** @brief Random number generator. */
    Random random;
    /** @brief String decay factor. */
    double decay_factor;
} KarplusStrongContext;

static double karplus_strong_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    KarplusStrongContext *context = (KarplusStrongContext *)context_;
    double pitch_tick = gen_eval(args[0], eval);
    double decay_tick = gen_eval(args[1], eval);
    if (eval == NULL || eval->compute_flag)
    {
        size_t size = (size_t)(1.0 / pitch_tick);
        buffer_resize(&context->buffer, size, &context->index);
        context->decay_factor = 0.5 * exp2(-decay_tick * (double)size);
    }
    double output = 0.0;
    double *samples = context->buffer.samples;
    if (samples != NULL)
    {
        size_t next = context->index + 1;
        if (next >= context->buffer.size)
        {
            next = 0;
        }
        samples[context->index] = (samples[context->index] + samples[next]) * context->decay_factor;
        output = samples[context->index];
        context->index = next;
    }
    return output;
}

static int karplus_strong_init(__U size_t count, __U Gen **args, void *context_)
{
    KarplusStrongContext *context = (KarplusStrongContext *)context_;
    context->buffer.filler = fill_rand_1_1;
    context->buffer.filler_context = &context->random;
    return csErrorNone;
}

static void karplus_strong_free(__U size_t count, void *context_)
{
    KarplusStrongContext *context = (KarplusStrongContext *)context_;
    buffer_free(&context->buffer);
}

/**
 * @brief Create a function that simulates a vibrating string using the
 * Karplus-Strong algorithm.
 *
 * The Karplus-Strong algorithm works by maintaining a circular buffer of
 * samples that are filtered and fed back into the buffer. The buffer length
 * determines the fundamental frequency, while the filtering process creates
 * natural-sounding decay characteristics.
 *
 * @param pitch_tick Function that controls the pitch of the string in periods
 *                   per sample. The buffer size will be 1/pitch_tick samples.
 * @param decay_tick Function that controls the decay time of the string. Higher
 *                   values create faster decay. The decay factor is calculated
 *                   as: 0.5 * 2^(-decay_tick * buffer_size)
 * @return Func* Karplus-Strong function that outputs plucked string sounds.
 */
Func *karplus_strong_create(Func *pitch_tick, Func *decay_tick)
{
    KarplusStrongContext initial = {.random = random_create(0)};
    return func_create(karplus_strong_init, karplus_strong_eval, karplus_strong_free, NULL, sizeof(KarplusStrongContext), &initial, FuncFlagNone, pitch_tick, decay_tick);
}

#endif // CSYNTH_KARPLUS_STRONG_H

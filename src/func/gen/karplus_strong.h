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
        context->decay_factor = 0.5 / exp2(decay_tick * (double)size);
    }
    double output = 0.0;
    double *samples = context->buffer.samples;
    if (samples != NULL)
    {
        size_t next = (context->index + 1) % context->buffer.size;
        samples[context->index] = (samples[context->index] + samples[next]) * context->decay_factor;
        output = samples[context->index];
        context->index = next;
    }
    return output;
}

static bool karplus_strong_init(__U size_t count, __U Gen **args, void *context_)
{
    KarplusStrongContext *context = (KarplusStrongContext *)context_;
    context->buffer.filler = fill_rand_1_1;
    context->buffer.filler_context = &context->random;
    return false;
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
 * @param pitch_tick Function that controls the pitch of the string.
 * @param decay_tick Function that controls the decay of the string.
 * @return Func* Karplus-Strong function.
 */
Func *karplus_strong_create(Func *pitch_tick, Func *decay_tick)
{
    KarplusStrongContext initial = {.random = random_create(0)};
    return func_create(karplus_strong_init, karplus_strong_eval, karplus_strong_free, sizeof(KarplusStrongContext), &initial, FuncFlagNone, pitch_tick, decay_tick);
}

#endif // CSYNTH_KARPLUS_STRONG_H

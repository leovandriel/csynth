#ifndef CSYNTH_CHORUS_H
#define CSYNTH_CHORUS_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../mem/buffer.h"

/** @see chorus_create */
typedef struct
{
    /** @brief Buffer for storing delayed samples. */
    Buffer buffer;
    /** @brief Index of the next sample to write. */
    size_t index;
} ChorusContext;

static double chorus_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    ChorusContext *context = (ChorusContext *)context_;
    double tick = gen_eval(args[0], eval);
    double modulation = gen_eval(args[1], eval);
    double delay = gen_eval(args[2], eval);
    double depth = gen_eval(args[3], eval);
    double input = gen_eval(args[4], eval);
    if (eval == NULL || eval->compute_flag)
    {
        size_t size = (size_t)(delay / tick);
        buffer_resize(&context->buffer, size, &context->index);
    }
    double output = input;
    double *samples = context->buffer.samples;
    if (samples != NULL)
    {
        size_t offset = (size_t)(depth / tick * modulation + (double)context->buffer.size * 0.5);
        // size_t offset = (size_t)(depth / eval.params[EvalParamPitchTick] *
        // (modulation + 1) * 0.5);
        size_t index = (context->index + context->buffer.size - offset) % context->buffer.size;
        output = 0.5 * (input + samples[index]);
        samples[context->index] = input;
        context->index = (context->index + 1) % context->buffer.size;
    }
    return output;
}

static void chorus_free(__U size_t count, void *context_)
{
    ChorusContext *context = (ChorusContext *)context_;
    buffer_free(&context->buffer);
}

/**
 * @brief Create a function that implements a chorus effect.
 *
 * @param tick Periods per sample.
 * @param modulation Modulation signal, typically a sine wave.
 * @param delay Delay time in seconds, typically 20ms.
 * @param depth Modulation depth in seconds, typically 3ms.
 * @param input Input signal.
 * @return Func* Chorus function.
 */
Func *chorus_create(Func *tick, Func *modulation, Func *delay, Func *depth, Func *input)
{
    return func_create(NULL, chorus_eval, chorus_free, NULL, sizeof(ChorusContext), NULL, FuncFlagNone, tick, modulation, delay, depth, input);
}

#endif // CSYNTH_CHORUS_H

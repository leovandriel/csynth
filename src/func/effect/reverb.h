#ifndef CSYNTH_REVERB_H
#define CSYNTH_REVERB_H

#include <stdlib.h>
#include <string.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../mem/buffer.h"

/** @see reverb_create */
typedef struct
{
    /** @brief Buffer to store samples. */
    Buffer buffer;
    /** @brief Index of the next sample. */
    size_t index;
} ReverbContext;

static double reverb_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    ReverbContext *context = (ReverbContext *)context_;
    double tick = gen_eval(args[0], eval);
    double decay = gen_eval(args[1], eval);
    double input = gen_eval(args[2], eval);
    if (eval == NULL || eval->compute_flag)
    {
        size_t size = (size_t)(1.0 / tick);
        buffer_resize(&context->buffer, size, &context->index);
    }
    double *samples = context->buffer.samples;
    double output = input;
    if (samples != NULL)
    {
        samples[context->index] = samples[context->index] * decay + input;
        output = samples[context->index];
        context->index = (context->index + 1) % context->buffer.size;
    }
    return output;
}

static void reverb_free(__U size_t count, void *context_)
{
    ReverbContext *context = (ReverbContext *)context_;
    buffer_free(&context->buffer);
}

/**
 * @brief Create a function that generates reverb, using fixed interval and
 * decay.
 *
 * @param tick Periods per sample.
 * @param decay Decay factor per period.
 * @param input Input signal.
 * @return Func* Reverb function.
 */
Func *reverb_create(Func *tick, Func *decay, Func *input)
{
    return func_create(NULL, reverb_eval, reverb_free, NULL, sizeof(ReverbContext), NULL, FuncFlagNone, tick, decay, input);
}

#endif // CSYNTH_REVERB_H

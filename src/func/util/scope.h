#ifndef CSYNTH_SCOPE_H
#define CSYNTH_SCOPE_H

#include <stdio.h>
#include <string.h>

#include "../../io/file.h"
#include "../../ui/render_pipe.h"
#include "../../util/error.h"
#include "../../util/math.h"
#include "../../util/worker.h"

#define SCOPE_BUFFER_COUNT 2
#define SCOPE_BUFFER_TYPE uint32_t

/** @see scope_create */
typedef struct
{
    /** @brief The number of periods to accumulate in the plot. */
    size_t periods;
    /** @brief The range of the input, typically slightly above one. */
    double range;
    /** @brief Image render target. */
    RenderPipe *pipe;
    /** @brief Gamma correction, brightens darker pixels. */
    int gamma;
    /** @brief Pixel buffer. */
    SCOPE_BUFFER_TYPE *buffers[SCOPE_BUFFER_COUNT];
    /** @brief Pixel buffer index. */
    size_t buffer_index;
    /** @brief The current phase of the plot. */
    double phase;
    /** @brief The count of periods accumulated. */
    size_t period_count;
    /** Async worker. */
    Worker worker;
} ScopeContext;

static void scope_job(void *context_)
{
    ScopeContext *context = (ScopeContext *)context_;
    uint32_t *out_buffer = NULL;
    size_t out_pitch = 0;
    if (render_pipe_lock(context->pipe, &out_buffer, &out_pitch) != 0)
    {
        return;
    }
    SCOPE_BUFFER_TYPE *buffer = context->buffers[(context->buffer_index + SCOPE_BUFFER_COUNT - 1) % SCOPE_BUFFER_COUNT];
    for (size_t j = 0; j < context->pipe->height; j++)
    {
        for (size_t i = 0; i < context->pipe->width; i++)
        {
            double value = (double)buffer[j * context->pipe->width + i] / (double)context->periods;
            uint32_t out = (uint32_t)math_clamp(math_gamma(value, context->gamma) * 0x100, 0, 0xFF);
            out_buffer[j * (out_pitch / sizeof(uint32_t)) + i] = 0xFF000000 | (out << 16) | (out << 8) | out;
        }
    }
    render_pipe_unlock(context->pipe);
}

static double scope_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    ScopeContext *context = (ScopeContext *)context_;
    double input = gen_eval(args[0], eval);
    double frequency = gen_eval(args[1], eval);
    size_t x_coord = (size_t)((double)context->pipe->width * context->phase);
    size_t y_coord = (size_t)((double)context->pipe->height * (input / context->range + 1) * 0.5);
    SCOPE_BUFFER_TYPE *buffer = context->buffers[context->buffer_index];
    buffer[y_coord * context->pipe->width + x_coord]++;
    context->phase += eval->params[EvalParamPitchTick] * frequency;
    if (context->phase >= 1.0)
    {
        context->phase -= 1.0;
        if (++context->period_count % context->periods == 0)
        {
            context->buffer_index = (context->buffer_index + 1) % SCOPE_BUFFER_COUNT;
            worker_run(&context->worker, scope_job, context);
            SCOPE_BUFFER_TYPE *buffer = context->buffers[context->buffer_index];
            memset(buffer, 0, context->pipe->width * context->pipe->height * sizeof(SCOPE_BUFFER_TYPE));
        }
    }
    return input;
}

static csError scope_init(__U size_t count, __U Gen **args, void *context_)
{
    ScopeContext *context = (ScopeContext *)context_;
    for (size_t i = 0; i < SCOPE_BUFFER_COUNT; i++)
    {
        context->buffers[i] = (SCOPE_BUFFER_TYPE *)malloc_(context->pipe->width * context->pipe->height * sizeof(SCOPE_BUFFER_TYPE));
        if (context->buffers[i] == NULL)
        {
            for (size_t j = 0; j < i; j++)
            {
                free_(context->buffers[j]);
            }
            return error_type(csErrorMemoryAlloc);
        }
    }
    return worker_init(&context->worker);
}

static void scope_free(__U size_t count, void *context_)
{
    ScopeContext *context = (ScopeContext *)context_;
    worker_free(&context->worker);
    for (size_t i = 0; i < SCOPE_BUFFER_COUNT; i++)
    {
        free_(context->buffers[i]);
    }
}

/**
 * @brief Creates a scope function that plots the wave of a given frequency.
 *
 * @param input The input function.
 * @param frequency The frequency of the plot, i.e. which frequency will be
 * primarily visible.
 * @param range The range of the input, typically slightly above one.
 * @param filename The name of the file to save the image.
 * @param width The width of the image.
 * @param height The height of the image.
 * @param gamma Gamma correction, brightens darker pixels.
 * @param periods The number of periods to accumulate in the plot.
 * @return A pointer to the created scope function.
 */
Func *scope_create(Func *input, Func *frequency, size_t periods, double range, RenderPipe *pipe, int gamma)
{
    ScopeContext initial = {
        .periods = periods,
        .range = range,
        .pipe = pipe,
        .gamma = gamma,
    };
    return func_create(scope_init, scope_eval, scope_free, NULL, sizeof(ScopeContext), &initial, FuncFlagNone, input, frequency);
}

#endif // CSYNTH_SCOPE_H

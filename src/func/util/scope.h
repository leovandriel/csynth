#ifndef CSYNTH_SCOPE_H
#define CSYNTH_SCOPE_H

#include <stdio.h>
#include <string.h>

#include "../../io/file.h"
#include "../../ui/render_pipe.h"
#include "../../util/error.h"
#include "../../util/math.h"
#include "../../util/worker.h"
#include "../../util/fourier.h"

/** @see scope_create */
typedef struct
{
    /** @brief The range of the input, typically slightly above one. */
    double range;
    /** @brief Image render target. */
    RenderPipe *pipe;
    /** @brief Whether to auto-detect the tick frequency. */
    bool auto_detect;
    /** @brief The detected tick frequency. */
    double detected_tick;
    /** @brief Sample input buffer. */
    double *input_buffer;
    /** @brief Sample phase buffer. */
    double *phase_buffer;
    /** @brief The number of trailing samples to display. */
    size_t trail_count;
    /** @brief The number of samples added to the buffer, up to trail_count. */
    size_t trail_index;
    /** @brief The number of samples between renders. */
    size_t render_count;
    /** @brief The number of samples since last render, up to render_count. */
    size_t render_index;
    /** @brief The current phase of the plot. */
    double phase;
    /** @brief Render buffer. */
    double *input_render;
    double *phase_render;
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
    memset(out_buffer, 0, context->pipe->width * context->pipe->height * sizeof(uint32_t));
    for (size_t i = 0; i < context->trail_count; i++)
    {
        double phase = context->phase_render[i];
        double input = context->input_render[i];
        size_t x_coord = (size_t)round(phase * (double)context->pipe->width);
        size_t y_coord = (size_t)((double)context->pipe->height * (input / context->range + 1) * 0.5);
        uint32_t out = (uint32_t)math_clamp((double)0x100 * (double)i / (double)context->trail_count, 0, 0xFF);
        out_buffer[y_coord * context->pipe->width + x_coord] = 0xFF000000 | (out << 16) | (out << 8) | out;
    }
    render_pipe_unlock(context->pipe);
    if (context->auto_detect)
    {
        double db = 0.0, frequency = 0.0;
        fourier_find_dominant(context->input_render, context->trail_count, 1, &frequency, &db);
        context->detected_tick = frequency;
    }
}

static double scope_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    ScopeContext *context = (ScopeContext *)context_;
    double input = gen_eval(args[0], eval);
    context->input_buffer[context->trail_index] = input;
    context->phase_buffer[context->trail_index] = context->phase;
    if (++context->trail_index >= context->trail_count)
    {
        context->trail_index = 0;
    }
    if (++context->render_index >= context->render_count)
    {
        context->render_index = 0;
        memcpy(context->input_render, context->input_buffer, context->trail_count * sizeof(double));
        memcpy(context->phase_render, context->phase_buffer, context->trail_count * sizeof(double));
        worker_run(&context->worker, scope_job, context);
    }
    context->phase += context->auto_detect ? context->detected_tick : gen_eval(args[1], eval);
    if (context->phase >= 1.0)
    {
        context->phase -= 1.0;
    }
    return input;
}

static csError scope_init(__U size_t count, __U Gen **args, void *context_)
{
    ScopeContext *context = (ScopeContext *)context_;
    context->input_buffer = (double *)calloc_(context->trail_count, sizeof(double));
    if (context->input_buffer == NULL)
    {
        return error_type(csErrorMemoryAlloc);
    }
    context->phase_buffer = (double *)calloc_(context->trail_count, sizeof(double));
    if (context->phase_buffer == NULL)
    {
        free_(context->input_buffer);
        return error_type(csErrorMemoryAlloc);
    }
    context->input_render = (double *)calloc_(context->trail_count, sizeof(double));
    if (context->input_render == NULL)
    {
        free_(context->phase_buffer);
        free_(context->input_buffer);
        return error_type(csErrorMemoryAlloc);
    }
    context->phase_render = (double *)calloc_(context->trail_count, sizeof(double));
    if (context->phase_render == NULL)
    {
        free_(context->phase_buffer);
        free_(context->input_render);
        free_(context->input_buffer);
        return error_type(csErrorMemoryAlloc);
    }
    return worker_init(&context->worker);
}

static void scope_free(__U size_t count, void *context_)
{
    ScopeContext *context = (ScopeContext *)context_;
    worker_free(&context->worker);
    free_(context->input_buffer);
    free_(context->phase_buffer);
    free_(context->input_render);
    free_(context->phase_render);
}

/**
 * @brief Creates a scope function that plots the wave of a given frequency.
 *
 * @param tick The frequency of the plot, i.e. which frequency will be primarily visible. NULL for auto-detect.
 * @param samples The number of trailing samples to display.
 * @param range The range of the input, typically slightly above one.
 * @param pipe The render pipe to use.
 * @param input The input function.
 * @return A pointer to the created scope function.
 */
Func *scope_create(Func *tick, size_t trail_exp, size_t render_exp, double range, RenderPipe *pipe, Func *input)
{
    ScopeContext initial = {
        .trail_count = 1 << trail_exp,
        .render_count = 1 << render_exp,
        .range = range,
        .pipe = pipe,
        .auto_detect = tick,
    };
    if (tick == NULL)
    {
        return func_create(scope_init, scope_eval, scope_free, NULL, sizeof(ScopeContext), &initial, FuncFlagNone, input);
    }
    else
    {
        return func_create(scope_init, scope_eval, scope_free, NULL, sizeof(ScopeContext), &initial, FuncFlagNone, input, tick);
    }
}

#endif // CSYNTH_SCOPE_H

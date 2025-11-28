#ifndef CSYNTH_GRAM_H
#define CSYNTH_GRAM_H

#include <complex.h>
#include <stdio.h>
#include <string.h>

#include "../../io/file.h"
#include "../../ui/render_pipe.h"
#include "../../util/error.h"
#include "../../util/fourier.h"
#include "../../util/worker.h"

/** @see gram_create */
typedef struct
{
    /** @brief The name of the file to save the image. */
    const char *filename;
    /** @brief The number of samples per frame. */
    size_t window_size;
    /** @brief Image render target. */
    RenderPipe *pipe;
    /** @brief Sample buffer. */
    double *window_buffer;
    /** @brief Pixel buffer. */
    double *magnitude_buffer;
    /** @brief Offset in sample buffer. */
    size_t window_offset;
    /** @brief Number of frames added. */
    size_t frame_index;
    /** Async worker. */
    Worker worker;
} GramContext;

static void gram_job(void *context_)
{
    GramContext *context = (GramContext *)context_;
    uint32_t *out_buffer = NULL;
    size_t out_pitch = 0;
    if (render_pipe_lock(context->pipe, &out_buffer, &out_pitch) != 0)
    {
        return;
    }
    fourier_to_rgb(context->magnitude_buffer, context->frame_index, out_buffer, out_pitch / sizeof(uint32_t), context->pipe->width, context->pipe->height);
    render_pipe_unlock(context->pipe);
}

static double gram_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    GramContext *context = (GramContext *)context_;
    double input = gen_eval(args[0], eval);
    context->window_buffer[context->window_offset++] = input;
    if (context->window_offset % (context->window_size / 2) == 0)
    {
        if (context->window_offset == context->window_size)
        {
            context->window_offset = 0;
        }
        double *out_buffer = context->magnitude_buffer + context->pipe->height * context->frame_index;
        fourier_transform(context->window_buffer, context->window_size, context->window_offset, out_buffer);
        context->frame_index = (context->frame_index + 1) % context->pipe->width;
        worker_run(&context->worker, gram_job, context);
    }
    return input;
}

static csError gram_init(__U size_t count, __U Gen **args, void *context_)
{
    GramContext *context = (GramContext *)context_;
    context->window_buffer = (double *)malloc_(context->window_size * sizeof(double));
    if (context->window_buffer == NULL)
    {
        return error_type(csErrorMemoryAlloc);
    }
    context->magnitude_buffer = (double *)malloc_(context->pipe->width * context->pipe->height * sizeof(double));
    if (context->magnitude_buffer == NULL)
    {
        free_(context->window_buffer);
        return error_type(csErrorMemoryAlloc);
    }
    return worker_init(&context->worker);
}

static void gram_free(__U size_t count, void *context_)
{
    GramContext *context = (GramContext *)context_;
    worker_free(&context->worker);
    free_(context->window_buffer);
    free_(context->magnitude_buffer);
}

/**
 * @brief Creates a gram function that plots the spectrogram.
 *
 * @param input The input function.
 * @param pipe Render pipe, defines height and width. `pipe->height` must be a power of 2. FFT window_size is `pipe->height * 2`.
 * @return A pointer to the created gram function.
 */
Func *gram_create(Func *input, RenderPipe *pipe)
{
    if (!fourier_is_power_of_two(pipe->height))
    {
        return error_null_message(csErrorInvalidArgument, "Pipe height must be a power of 2, got %zu", pipe->height);
    }
    GramContext initial = {
        .window_size = pipe->height * 2,
        .pipe = pipe,
    };
    return func_create(gram_init, gram_eval, gram_free, NULL, sizeof(GramContext), &initial, FuncFlagNone, input);
}

#endif // CSYNTH_GRAM_H

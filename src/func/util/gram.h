#ifndef CSYNTH_GRAM_H
#define CSYNTH_GRAM_H

#include <complex.h>
#include <stdio.h>
#include <string.h>

#include "../../io/file.h"
#include "../../io/ppm_header.h"
#include "../../ui/render_pipe.h"
#include "../../util/error.h"
#include "../../util/math.h"
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
    /** @brief Gamma correction, brightens darker pixels. */
    int gamma;
    /** @brief Sample buffer. */
    double *sample_buffer;
    /** @brief Pixel buffer. */
    unsigned char *magnitude_buffer;
    /** @brief Offset in sample buffer. */
    size_t sample_offset;
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
    for (size_t j = 0; j < context->pipe->height; j++)
    {
        for (size_t i = 0; i < context->pipe->width; i++)
        {
            unsigned char out = context->magnitude_buffer[((i + context->frame_index) % context->pipe->width) * context->pipe->height + j];
            out_buffer[j * (out_pitch / sizeof(uint32_t)) + i] = 0xFF000000 | (out << 16) | (out << 8) | out;
        }
    }
    render_pipe_unlock(context->pipe);
}

static void gram_add(GramContext *context)
{
    unsigned char *buffer = context->magnitude_buffer + context->pipe->height * context->frame_index;
    complex double fft_input[context->window_size];
    for (size_t i = 0; i < context->window_size; i++)
    {
        double hanning = (0.5 - 0.5 * cos(2.0 * M_PI * (double)i / (double)context->window_size));
        fft_input[i] = context->sample_buffer[(context->sample_offset + i) % context->window_size] * hanning;
    }
    math_fft(fft_input, context->window_size);
    for (size_t j = 0; j < context->pipe->height; j++)
    {
        double magnitude = cabs(fft_input[j / 2]) * 4.0 / (double)context->window_size;
        double corrected = 1 - math_pow_int(1 - magnitude, context->gamma);
        buffer[context->pipe->height - 1 - j] = (unsigned char)(255.0 * corrected);
    }
}

static double gram_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    GramContext *context = (GramContext *)context_;
    double input = gen_eval(args[0], eval);
    context->sample_buffer[context->sample_offset++] = input;
    if (context->sample_offset % (context->window_size / 2) == 0)
    {
        if (context->sample_offset == context->window_size)
        {
            context->sample_offset = 0;
        }
        gram_add(context);
        context->frame_index = (context->frame_index + 1) % context->pipe->width;
        worker_run(&context->worker, gram_job, context);
    }
    return input;
}

static csError gram_init(__U size_t count, __U Gen **args, void *context_)
{
    GramContext *context = (GramContext *)context_;
    context->sample_buffer = (double *)malloc_(context->window_size * sizeof(double));
    if (context->sample_buffer == NULL)
    {
        return error_type(csErrorMemoryAlloc);
    }
    context->magnitude_buffer = (unsigned char *)malloc_(context->pipe->width * context->pipe->height * sizeof(unsigned char));
    if (context->magnitude_buffer == NULL)
    {
        free_(context->sample_buffer);
        return error_type(csErrorMemoryAlloc);
    }
    return worker_init(&context->worker);
}

static void gram_free(__U size_t count, void *context_)
{
    GramContext *context = (GramContext *)context_;
    worker_free(&context->worker);
    free_(context->sample_buffer);
    free_(context->magnitude_buffer);
}

/**
 * @brief Creates a gram function that plots the spectrogram to a PPM image file.
 *
 * @param input The input function.
 * @param frame_count Number of frames per image, i.e. image width.
 * @param window_size Number of samples per window, i.e. max image height.
 * @param height Image height, truncating top if below window_size.
 * @param filename The name of the file to save the image. Include %i for image index.
 * @param gamma Gamma correction, brightens darker pixels.
 * @return A pointer to the created gram function.
 */
Func *gram_create(Func *input, size_t window_size, RenderPipe *pipe, int gamma)
{
    GramContext initial = {
        .window_size = window_size,
        .pipe = pipe,
        .gamma = gamma,
    };
    return func_create(gram_init, gram_eval, gram_free, NULL, sizeof(GramContext), &initial, FuncFlagNone, input);
}

#endif // CSYNTH_GRAM_H

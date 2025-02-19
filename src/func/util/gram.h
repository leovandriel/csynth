#ifndef CSYNTH_GRAM_H
#define CSYNTH_GRAM_H

#include <complex.h>
#include <stdio.h>
#include <string.h>

#include "../../io/file.h"
#include "../../io/ppm_header.h"
#include "../../util/error.h"
#include "../../util/math.h"
#include "../../util/worker.h"

#define GRAM_WRITER_BUFFER_SIZE 4096
#define GRAM_BUFFER_COUNT 2
#define GRAM_COLOR_DEPTH 3

/** @see gram_create */
typedef struct
{
    /** @brief The name of the file to save the image. */
    const char *filename;
    /** @brief The number frames. */
    size_t frame_count;
    /** @brief The number of samples per frame. */
    size_t window_size;
    /** @brief Image height. */
    size_t height;
    /** @brief Gamma correction, brightens darker pixels. */
    int gamma;
    /** @brief Sample buffer. */
    double *sample_buffer;
    /** @brief Pixel buffer. */
    unsigned char *magnitude_buffers[GRAM_BUFFER_COUNT];
    /** @brief Current buffer index. */
    size_t buffer_index;
    /** @brief Offset in sample buffer. */
    size_t sample_offset;
    /** @brief Number of frames added. */
    size_t frame_index;
    /** @brief Number of images. */
    size_t image_index;
    /** Async worker. */
    Worker worker;
} GramContext;

void gram_add(GramContext *context)
{
    unsigned char *magnitude_buffer = context->magnitude_buffers[context->buffer_index];
    unsigned char *buffer = magnitude_buffer + context->height * context->frame_index;
    complex double fft_input[context->window_size];
    for (size_t i = 0; i < context->window_size; i++)
    {
        double hanning = (0.5 - 0.5 * cos(2.0 * M_PI * (double)i / (double)context->window_size));
        fft_input[i] = context->sample_buffer[(context->sample_offset + i) % context->window_size] * hanning;
    }
    math_fft(fft_input, context->window_size);
    for (size_t j = 0; j < context->height; j++)
    {
        double magnitude = cabs(fft_input[j / 2]) * 4.0 / (double)context->window_size;
        double corrected = 1 - math_pow_int(1 - magnitude, context->gamma);
        buffer[context->height - 1 - j] = (unsigned char)(255.0 * corrected);
    }
}

static void gram_job(void *context_)
{
    GramContext *context = (GramContext *)context_;
    char filename[256];
    snprintf(filename, 256, context->filename, (int)context->image_index);
    FILE *file = fopen_(filename, "wb");
    if (file == NULL)
    {
        return;
    }
    ppm_header_write(file, context->frame_count, context->height);
    unsigned char *magnitude_buffer = context->magnitude_buffers[(context->buffer_index + GRAM_BUFFER_COUNT - 1) % GRAM_BUFFER_COUNT];
    unsigned char write_buffer[GRAM_WRITER_BUFFER_SIZE];
    unsigned char *out = write_buffer, *out_end = write_buffer + GRAM_WRITER_BUFFER_SIZE;
    for (size_t j = 0; j < context->height; j++)
    {
        for (size_t i = 0; i < context->frame_count; i++)
        {
            for (size_t k = 0; k < GRAM_COLOR_DEPTH; k++)
            {
                *(out++) = magnitude_buffer[i * context->height + j];
                if (out == out_end)
                {
                    fwrite(write_buffer, sizeof(unsigned char), out - write_buffer, file);
                    out = write_buffer;
                }
            }
        }
    }
    fwrite(write_buffer, sizeof(unsigned char), out - write_buffer, file);
    fclose_(file);
    log_info("Spectrogram saved to %s", filename);
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
        if (++context->frame_index == context->frame_count)
        {
            context->buffer_index = (context->buffer_index + 1) % GRAM_BUFFER_COUNT;
            worker_run(&context->worker, gram_job, context);
            context->frame_index = 0;
            context->image_index++;
        }
    }
    return input;
}

static int gram_init(__U size_t count, __U Gen **args, void *context_)
{
    GramContext *context = (GramContext *)context_;
    context->sample_buffer = (double *)malloc_(context->window_size * sizeof(double));
    if (context->sample_buffer == NULL)
    {
        return error_type(csErrorMemoryAlloc);
    }
    for (size_t i = 0; i < GRAM_BUFFER_COUNT; i++)
    {
        context->magnitude_buffers[i] = (unsigned char *)malloc_(context->frame_count * context->height * GRAM_COLOR_DEPTH * sizeof(unsigned char));
        if (context->magnitude_buffers[i] == NULL)
        {
            for (size_t j = 0; j < i; j++)
            {
                free_(context->magnitude_buffers[j]);
            }
            free_(context->sample_buffer);
            return error_type(csErrorMemoryAlloc);
        }
    }
    return worker_init(&context->worker);
}

static void gram_free(__U size_t count, void *context_)
{
    GramContext *context = (GramContext *)context_;
    worker_free(&context->worker);
    free_(context->sample_buffer);
    for (size_t i = 0; i < GRAM_BUFFER_COUNT; i++)
    {
        free_(context->magnitude_buffers[i]);
    }
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
Func *gram_create(Func *input, size_t frame_count, size_t window_size, size_t height, const char *filename, int gamma)
{
    GramContext initial = {
        .frame_count = frame_count,
        .window_size = window_size,
        .height = height,
        .filename = filename,
        .gamma = gamma,
    };
    return func_create(gram_init, gram_eval, gram_free, NULL, sizeof(GramContext), &initial, FuncFlagNone, input);
}

#endif // CSYNTH_GRAM_H

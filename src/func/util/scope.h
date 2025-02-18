#ifndef CSYNTH_SCOPE_H
#define CSYNTH_SCOPE_H

#include <stdio.h>
#include <string.h>

#include "../../io/file.h"
#include "../../io/ppm_header.h"
#include "../../util/error.h"
#include "../../util/math.h"

#define SCOPE_COLOR_DEPTH 3
#define WRITER_BUFFER_SIZE 4096

/** @see scope_create */
typedef struct
{
    /** @brief The number of periods to accumulate in the plot. */
    size_t periods;
    /** @brief The range of the input, typically slightly above one. */
    double range;
    /** @brief The name of the file to save the image. */
    const char *filename;
    /** @brief The width of the image. */
    size_t width;
    /** @brief The height of the image. */
    size_t height;
    /** @brief Gamma correction, brightens darker pixels. */
    int gamma;
    /** @brief Pixel buffer. */
    size_t *buffer;
    /** @brief The current phase of the plot. */
    double phase;
    /** @brief The count of periods accumulated. */
    size_t period_count;
    /** @brief The current image index. */
    size_t image_index;
} ScopeContext;

static csError scope_write(ScopeContext *context)
{
    char filename[256];
    snprintf(filename, 256, context->filename, (int)context->image_index);
    FILE *file = fopen_(filename, "w");
    if (file == NULL)
    {
        return error_type(csErrorFileOpen);
    }
    ppm_header_write(file, context->width, context->height);
    size_t size = context->width * context->height * SCOPE_COLOR_DEPTH;
    unsigned char write_buffer[WRITER_BUFFER_SIZE];
    unsigned char *out = write_buffer, *out_end = write_buffer + WRITER_BUFFER_SIZE;
    for (size_t *in = context->buffer, *in_end = in + size; in < in_end; in++)
    {
        double value = (double)(*in / context->periods);
        double corrected = (1 - math_pow_int(1 - value / 255.0, context->gamma)) * 255.0;
        *(out++) = (unsigned char)corrected;
        if (out == out_end)
        {
            fwrite(write_buffer, sizeof(unsigned char), out - write_buffer, file);
            out = write_buffer;
        }
    }
    fwrite(write_buffer, sizeof(unsigned char), out - write_buffer, file);
    fclose_(file);
    log_info("Oscilloscope saved to %s", filename);
    return csErrorNone;
}

static double scope_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    ScopeContext *context = (ScopeContext *)context_;
    double input = gen_eval(args[0], eval);
    double frequency = gen_eval(args[1], eval);
    size_t x_coord = (size_t)((double)context->width * context->phase);
    size_t y_coord = (size_t)((double)context->height * (input / context->range + 1) * 0.5);
    size_t *buffer = &context->buffer[(y_coord * context->width - x_coord) * SCOPE_COLOR_DEPTH];
    *(buffer++) += 255;
    *(buffer++) += 255;
    *(buffer++) += 255;
    context->phase += eval->params[EvalParamPitchTick] * frequency;
    if (context->phase >= 1.0)
    {
        context->phase -= 1.0;
        if (++context->period_count % context->periods == 0)
        {
            scope_write(context);
            memset(context->buffer, 0, context->width * context->height * SCOPE_COLOR_DEPTH * sizeof(size_t));
            context->image_index++;
        }
    }
    return input;
}

static int scope_init(__U size_t count, __U Gen **args, void *context_)
{
    ScopeContext *context = (ScopeContext *)context_;
    context->buffer = (size_t *)malloc_(context->width * context->height * SCOPE_COLOR_DEPTH * sizeof(size_t));
    if (context->buffer == NULL)
    {
        return error_type(csErrorMemoryAlloc);
    }
    return csErrorNone;
}

static void scope_free(__U size_t count, void *context_)
{
    ScopeContext *context = (ScopeContext *)context_;
    free_(context->buffer);
}

/**
 * @brief Creates a scope function that plots the wave of a given frequency to
 * a PPM image file.
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
Func *scope_create(Func *input, Func *frequency, size_t periods, double range, const char *filename, size_t width, size_t height, int gamma)
{
    ScopeContext initial = {
        .periods = periods,
        .range = range,
        .filename = filename,
        .width = width,
        .height = height,
        .gamma = gamma,
    };
    return func_create(scope_init, scope_eval, scope_free, NULL, sizeof(ScopeContext), &initial, FuncFlagNone, input, frequency);
}

#endif // CSYNTH_SCOPE_H

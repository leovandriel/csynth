#ifndef CSYNTH_RECORD_H
#define CSYNTH_RECORD_H

#include <stdio.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../io/writer.h"

/** @see record_create */
typedef struct
{
    /** @brief Buffer for keeping samples until flush to file. */
    sample_t buffer[WRITER_BUFFER_SIZE];
    /** @brief Current offset in the buffer. */
    size_t offset;
    /** @brief Number of samples written to the file. */
    size_t size;
    /** @brief Filename of the output file. */
    const char *filename;
    /** @brief File handle for writing samples. */
    FILE *file;
    /** @brief Sample rate of the output file. */
    size_t sample_rate;
} RecordContext;

static double record_eval(size_t count, Gen **args, Eval *eval, void *context_)
{
    RecordContext *context = (RecordContext *)context_;
    double sum = 0.0;
    for (size_t channel = 0; channel < count; channel++)
    {
        double output = gen_eval(args[channel], eval);
        context->buffer[context->offset++] = sampler_quantize(output);
        if (context->offset == WRITER_BUFFER_SIZE)
        {
            fwrite(context->buffer, sizeof(sample_t), context->offset, context->file);
            context->offset = 0;
        }
        context->size++;
        sum += output;
    }
    return sum;
}

static bool record_init(size_t count, __U Gen **args, void *context_)
{
    RecordContext *context = (RecordContext *)context_;
    FILE *file = fopen(context->filename, "wb");
    if (file == NULL)
    {
        return error_catch_message(csErrorFileOpen, "Unable to open file: %s", context->filename);
    }
    context->file = file;
    csError error = wav_header_write(1, (uint32_t)count, context->file, context->sample_rate);
    return error_catch(error);
}

static void record_free(size_t count, void *context_)
{
    RecordContext *context = (RecordContext *)context_;
    size_t write_count = fwrite(context->buffer, sizeof(sample_t), context->offset, context->file);
    if (write_count != context->offset)
    {
        error_catch(csErrorFileWrite);
    }
    if (fseek(context->file, 0, SEEK_SET))
    {
        error_catch(csErrorFileSeek);
    }
    csError error = wav_header_write((uint32_t)context->size, (uint32_t)count, context->file, context->sample_rate);
    if (error != csErrorNone)
    {
        error_catch(error);
    }
    if (fclose(context->file) == EOF)
    {
        error_catch(csErrorFileClose);
    }
}

/**
 * @brief Create a function that records samples to a file.
 *
 * @param filename Output filename.
 * @param sample_rate Sample rate of the output file, e.g. 44100.
 * @param count Number of channels.
 * @param args Input signals.
 * @return Func* Record function.
 */
Func *record_create(const char *filename, size_t sample_rate, size_t count, Func **args)
{
    RecordContext initial = {
        .filename = filename,
        .sample_rate = sample_rate,
    };
    return func_create_args(record_init, record_eval, record_free, sizeof(RecordContext), &initial, FuncFlagNone, count, args, "input");
}

#endif // CSYNTH_RECORD_H

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
    /** @brief File handle for output. */
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

static int record_init(size_t count, __U Gen **args, void *context_)
{
    RecordContext *context = (RecordContext *)context_;
    WavHeader header = {0};
    wav_header_write(&header, 1, (uint32_t)count, context->sample_rate);
    size_t header_count = fwrite(&header, sizeof(header), 1, context->file);
    if (header_count != 1)
    {
        return error_type(csErrorFileWrite);
    }
    return csErrorNone;
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
    WavHeader header = {0};
    wav_header_write(&header, (uint32_t)context->size, (uint32_t)count, context->sample_rate);
    size_t header_count = fwrite(&header, sizeof(header), 1, context->file);
    if (header_count != 1)
    {
        error_catch(csErrorFileWrite);
    }
}

static void record_cleanup(void *initial_)
{
    RecordContext *initial = (RecordContext *)initial_;
    if (fclose(initial->file) == EOF)
    {
        error_catch(csErrorFileClose);
    }
}

/**
 * @brief Create a function that records samples to a WAV file handle.
 *
 * @param file Output FILE handle.
 * @param sample_rate Sample rate of the output file, e.g. 44100.
 * @param count Number of channels.
 * @param args Input signals.
 * @return Func* Record function.
 */
Func *record_create(FILE *file, size_t sample_rate, size_t count, Func **args)
{
    RecordContext initial = {
        .file = file,
        .sample_rate = sample_rate,
    };
    return func_create_args(record_init, record_eval, record_free, record_cleanup, sizeof(RecordContext), &initial, FuncFlagNone, count, args, "input");
}

Func *record_filename(const char *filename, size_t sample_rate, size_t count, Func **args)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        error_catch_message(csErrorFileOpen, "Failed to open file %s", filename);
        return NULL;
    }
    return record_create(file, sample_rate, count, args);
}

#endif // CSYNTH_RECORD_H

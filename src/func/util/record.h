//
// record.h - Record to file
//
#ifndef CSYNTH_RECORD_H
#define CSYNTH_RECORD_H

#include <stdio.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../io/writer.h"

typedef struct
{
    sample_t buffer[WRITER_BUFFER_SIZE];
    size_t offset;
    size_t size;
    const char *filename;
    FILE *file;
    int sample_rate;
} RecordContext;

static double record_eval(int count, Gen **args, EvalContext *eval, void *context_)
{
    RecordContext *context = (RecordContext *)context_;
    double sum = 0;
    for (int channel = 0; channel < count; channel++)
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

static int record_init(int count, __U Gen **args, void *context_)
{
    RecordContext *context = (RecordContext *)context_;
    FILE *file = fopen(context->filename, "wb");
    if (file == NULL)
    {
        return error_catch_message(csErrorFileOpen, "Unable to open file: %s", context->filename);
    }
    context->file = file;
    csError error = wav_header_write(1, count, context->file, context->sample_rate);
    return error_catch(error);
}

static void record_free(int count, void *context_)
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
    csError error = wav_header_write(context->size, count, context->file, context->sample_rate);
    if (error != csErrorNone)
    {
        error_catch(error);
    }
    if (fclose(context->file) == EOF)
    {
        error_catch(csErrorFileClose);
    }
}

Func *record_create(const char *filename, int sample_rate, int count, Func **args)
{
    RecordContext initial = {
        .filename = filename,
        .sample_rate = sample_rate,
    };
    return func_create(record_init, record_eval, record_free, sizeof(RecordContext), &initial, FuncFlagNone, count, args);
}

#endif // CSYNTH_RECORD_H

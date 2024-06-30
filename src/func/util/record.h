//
// record.h - Record to file
//
#ifndef CSYNTH_RECORD_H
#define CSYNTH_RECORD_H

#include <stdio.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../io/writer.h"
#include "../../util/default.h"

typedef struct
{
    sample_t buffer[WRITER_BUFFER_SIZE];
    size_t offset;
    size_t size;
    const char *filename;
    FILE *file;
    int sample_rate;
} RecordContext;

static double record_eval(int count, Gen **args, Eval eval, void *context_)
{
    RecordContext *context = (RecordContext *)context_;
    double sum = 0;
    for (int channel = 0; channel < count; channel++)
    {
        double output = gen_eval(args[channel], eval);
        double clip = output > 1.0 ? 1.0 : (output < -1.0 ? -1.0 : output);
        context->buffer[context->offset++] = (sample_t)(clip * 32767);
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

Func *record_array(const char *filename, int sample_rate, int count, Func **args)
{
    RecordContext initial = {
        .filename = filename,
        .sample_rate = sample_rate,
    };
    return func_create(record_init, record_eval, record_free, sizeof(RecordContext), &initial, FuncFlagNone, count, args);
}

#define record_channels(_filename, _sample_rate, ...) (record_array(_filename, _sample_rate, FUNCS(__VA_ARGS__)))

Func *record(const char *filename, Func *input) { return record_channels(filename, DEFAULT_SAMPLE_RATE, input); }
Func *record_(Func *input) { return record(DEFAULT_WAV_FILENAME, input); }
Func *record_stereo(const char *filename, Func *left, Func *right) { return record_channels(filename, DEFAULT_SAMPLE_RATE, left, right); }
Func *record_stereo_(Func *left, Func *right) { return record_stereo(DEFAULT_WAV_FILENAME, left, right); }

#endif // CSYNTH_RECORD_H

//
// record.h - Record to file
//
#ifndef CSYNTH_RECORD_H
#define CSYNTH_RECORD_H

#include <stdio.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../io/writer.h"
#include "../../util/config.h"

typedef struct
{
    sample_t buffer[WRITER_BUFFER_SIZE];
    size_t offset;
    size_t size;
    const char *filename;
    FILE *file;
} RecordContext;

static double record_eval(int count, Gen **args, __attribute__((unused)) double delta, void *context_)
{
    RecordContext *context = (RecordContext *)context_;
    double sum = 0;
    for (int channel = 0; channel < count; channel++)
    {
        double output = gen_eval(args[channel]);
        double clip = output > 1.0 ? 1.0 : (output < -1.0 ? -1.0 : output);
        context->buffer[context->offset++] = clip * 32767;
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

void record_init(int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    RecordContext *context = (RecordContext *)context_;
    context->file = fopen(context->filename, "wb");
    wav_header_write(1, count, context->file);
}

static void record_free(int count, void *context_)
{
    RecordContext *context = (RecordContext *)context_;
    fwrite(context->buffer, sizeof(sample_t), context->offset, context->file);
    fseek(context->file, 0, SEEK_SET);
    wav_header_write(context->size, count, context->file);
    fclose(context->file);
}

Func *record_args(const char *filename, int count, ...)
{
    va_list valist;
    va_start(valist, count);
    RecordContext initial = (RecordContext){
        .filename = filename,
    };
    Func *func = func_create_va(record_init, record_eval, record_free, sizeof(RecordContext), &initial, FUNC_FLAG_DEFAULT, count, valist);
    va_end(valist);
    return func;
}

#define record_channels(_filename, ...) (record_args(_filename, (sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))

Func *record_array(const char *filename, int count, Func **args)
{
    RecordContext initial = (RecordContext){
        .filename = filename,
    };
    return func_create_array(record_init, record_eval, record_free, sizeof(RecordContext), &initial, FUNC_FLAG_DEFAULT, count, args);
}

Func *record(Func *input, const char *filename) { return record_channels(filename, input); }
Func *record_(Func *input) { return record(input, config_default_wav_filename); }
Func *record_stereo(Func *left, Func *right, const char *filename) { return record_channels(filename, left, right); }
Func *record_stereo_(Func *left, Func *right) { return record_stereo(left, right, config_default_wav_filename); }

#endif // CSYNTH_RECORD_H

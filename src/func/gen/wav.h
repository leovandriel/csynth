//
// wav.h - Play WAV file
//
// `wav(filename, channel)`
//
#ifndef CSYNTH_WAV_H
#define CSYNTH_WAV_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/reader.h"
#include "../gen/const.h"

typedef struct
{
    ReaderSamples samples;
    const char *filename;
    int channel;
    double time;
} WavContext;

static double wav_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    WavContext *context = (WavContext *)context_;
    double factor = gen_eval(args[0]);
    sample_t sample = reader_sample(&context->samples, context->time * factor, context->channel);
    double output = (double)sample / 32767;
    context->time += delta;
    return output;
}

void wav_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    WavContext *context = (WavContext *)context_;
    reader_read_file(&context->samples, context->filename);
}

void wav_free(void *context_)
{
    WavContext *context = (WavContext *)context_;
    reader_free(&context->samples);
}

Func *wav_channel(const char *filename, int channel, Func *factor)
{
    WavContext initial = (WavContext){
        .filename = filename,
        .channel = channel,
    };
    return func_create(wav_init, wav_eval, wav_free, sizeof(WavContext), &initial, FUNC_FLAG_DEFAULT, 1, factor);
}

Func *wav_channel_(const char *filename, int channel, double factor)
{
    return wav_channel(filename, channel, const_(factor));
}

Func *wav(const char *filename)
{
    return wav_channel_(filename, 0, 1);
}

#endif // CSYNTH_WAV_H

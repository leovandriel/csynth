//
// wav.h - Play WAV file
//
// `wav(filename, channel)`
//
#ifndef CSYNTH_WAV_H
#define CSYNTH_WAV_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../io/reader.h"

typedef struct
{
    ReaderSamples samples;
    int channel;
    double time;
} WavContext;

static double wav_eval(__U int count, Gen **args, EvalContext *eval, void *context_)
{
    WavContext *context = (WavContext *)context_;
    sample_t sample = reader_sample(&context->samples, context->time, context->channel);
    double output = (double)sample / 32767;
    double tick = gen_eval(args[0], eval);
    context->time += tick;
    return output;
}

Func *wav_create(ReaderSamples samples, int channel, Func *tick)
{
    WavContext initial = {
        .samples = samples,
        .channel = channel,
    };
    return func_create(NULL, wav_eval, NULL, sizeof(WavContext), &initial, FuncFlagNone, FUNCS(tick));
}

Func *wav_filename(const char *filename, int channel, Func *input)
{
    ReaderSamples samples;
    if (reader_read_filename(&samples, filename) != csErrorNone)
    {
        return NULL;
    }
    return wav_create(samples, channel, input);
}

#endif // CSYNTH_WAV_H

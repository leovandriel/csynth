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
#include "../gen/const.h"

typedef struct
{
    ReaderSamples samples;
    int channel;
    double time;
} WavContext;

static double wav_eval(__U int count, Gen **args, Eval eval, void *context_)
{
    WavContext *context = (WavContext *)context_;
    sample_t sample = reader_sample(&context->samples, context->time, context->channel);
    double output = (double)sample / 32767;
    context->time += gen_eval(args[0], eval);
    return output;
}

Func *wav_samples(ReaderSamples samples, int channel, Func *tick)
{
    WavContext initial = {
        .samples = samples,
        .channel = channel,
    };
    return func_create(NULL, wav_eval, NULL, sizeof(WavContext), &initial, FuncFlagNone, FUNCS(tick));
}

Func *wav_samples_(ReaderSamples samples, int channel, Func *tick)
{
    return wav_samples(samples, channel, tick);
}

Func *wav_filename(const char *filename, int channel, Func *input)
{
    ReaderSamples samples;
    if (reader_read_filename(&samples, filename) != csErrorNone)
    {
        return NULL;
    }
    return wav_samples(samples, channel, input);
}

Func *wav_filename_(const char *filename, int channel, Func *input)
{
    return wav_filename(filename, channel, input);
}

#endif // CSYNTH_WAV_H

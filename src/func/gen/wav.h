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
#include "../../util/default.h"
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
    double factor = gen_eval(args[0], eval);
    sample_t sample = reader_sample(&context->samples, context->time * factor, context->channel);
    double output = (double)sample / 32767;
    context->time += eval.delta;
    return output;
}

Func *wav_samples(ReaderSamples samples, int channel, Func *factor)
{
    WavContext initial = (WavContext){
        .samples = samples,
        .channel = channel,
    };
    return func_create(NULL, wav_eval, NULL, sizeof(WavContext), &initial, FuncFlagNone, 1, factor);
}

Func *wav_samples_(ReaderSamples samples, int channel, double factor)
{
    return wav_samples(samples, channel, const_(factor));
}

Func *wav_filename(const char *filename, int channel, Func *factor)
{
    ReaderSamples samples;
    if (reader_read_filename(&samples, filename) != csErrorNone)
    {
        return NULL;
    }
    return wav_samples(samples, channel, factor);
}

Func *wav_filename_(const char *filename, int channel, double factor)
{
    return wav_filename(filename, channel, const_(factor));
}

Func *wav(const char *filename)
{
    return wav_filename_(filename, 0, 1);
}

Func *wav_()
{
    return wav(DEFAULT_WAV_FILENAME);
}

#endif // CSYNTH_WAV_H

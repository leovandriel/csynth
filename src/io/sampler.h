//
// sampler.h - Sampling multiple channels, e.g. stereophonic sound.
//
#ifndef CSYNTH_SAMPLER_H
#define CSYNTH_SAMPLER_H

#include "../core/func.h"
#include "../core/gen.h"
#include "../util/error.h"

#define SAMPLE_RATE 44100 // 44.1 kHz
#define DISPLAY_RATE 10   // 10 FPS
#define CONTROL_RATE 100  // 100 FPS
#define COMPUTE_RATE 1000 // 1000 FPS
#define VOLUME_MULTIPLIER 0.5

typedef int16_t sample_t;

typedef struct
{
    Gen **channels;
    size_t count;
    Eval eval;
} Sampler;

Sampler *sampler_create(size_t sample_rate, size_t count, Func **inputs)
{
    Sampler *sampler = (Sampler *)malloc_(sizeof(Sampler));
    if (sampler == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    Gen **channels = (Gen **)malloc_(count * sizeof(Gen *));
    if (channels == NULL)
    {
        free_(sampler);
        return error_null(csErrorMemoryAlloc);
    }
    for (size_t index = 0; index < count; index++)
    {
        Func *input = inputs[index];
        Gen *channel = gen_create(input);
        if (channel == NULL)
        {
            for (size_t i = 0; i < index; i++)
            {
                gen_free(channels[i]);
            }
            free_(channels);
            free_(sampler);
            return NULL;
        }
        channels[index] = channel;
    }
    double tick = 1.0 / (double)sample_rate;
    Eval eval = {.wall_tick = tick};
    eval.params[EvalParamControlTick] = CONTROL_RATE / (double)CONTROL_RATE;
    eval.params[EvalParamDisplayTick] = DISPLAY_RATE / (double)CONTROL_RATE;
    eval.params[EvalParamComputeTick] = COMPUTE_RATE / (double)CONTROL_RATE;
    eval.params[EvalParamPitchTick] = 1.0 / (double)CONTROL_RATE;
    eval.params[EvalParamTempoTick] = 1.0 / (double)CONTROL_RATE;
    eval.params[EvalParamSustainTick] = 1.0 / (double)CONTROL_RATE;
    *sampler = (Sampler){
        .channels = channels,
        .count = count,
        .eval = eval,
    };
    return sampler;
}

sample_t sampler_quantize(double output)
{
    double scaled = output * VOLUME_MULTIPLIER;
    double clip = scaled > 1.0 ? 1.0 : (scaled < -1.0 ? -1.0 : scaled);
    return (sample_t)(clip * 32767);
}

void sampler_sample(Sampler *sampler, size_t count, sample_t *buffer)
{
    for (size_t frame = 0; frame < count; frame++)
    {
        sampler->eval.wall_time += sampler->eval.wall_tick;
        for (size_t index = 0; index < sampler->count; index++)
        {
            double output = gen_eval(sampler->channels[index], &sampler->eval);
            *(buffer++) = sampler_quantize(output);
        }
    }
}

void sampler_free(Sampler *sampler)
{
    for (size_t index = 0; index < sampler->count; index++)
    {
        gen_free(sampler->channels[index]);
    }
    free_(sampler->channels);
    sampler->channels = NULL;
    free_(sampler);
}

size_t sampler_gen_count(Sampler *sampler)
{
    size_t sum = 0;
    for (size_t index = 0; index < sampler->count; index++)
    {
        sum += gen_count(sampler->channels[index]);
    }
    return sum;
}

#endif // CSYNTH_SAMPLER_H

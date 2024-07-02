//
// sampler.h - Sampling multiple channels, e.g. stereophonic sound.
//
#ifndef CSYNTH_SAMPLER_H
#define CSYNTH_SAMPLER_H

#include "../core/func.h"
#include "../core/gen.h"
#include "../func/time/times.h"
#include "../util/error.h"

#define SAMPLE_RATE 44100 // 44.1 kHz
#define DISPLAY_RATE 10   // 10 FPS
#define CONTROL_RATE 100  // 100 FPS
#define VOLUME_MULTIPLIER 0.5

typedef int16_t sample_t;

typedef struct
{
    Gen **channels;
    int count;
    Eval eval;
} Sampler;

Sampler *sampler_create(int sample_rate, int count, Func **inputs)
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
    for (int index = 0; index < count; index++)
    {
        Func *input = inputs[index];
        input = scale_(EvalTickControl, CONTROL_RATE, input);
        input = scale_(EvalTickDisplay, DISPLAY_RATE, input);
        Gen *channel = gen_create(input);
        if (channel == NULL)
        {
            for (int i = 0; i < index; i++)
            {
                gen_free(channels[i]);
            }
            free_(channels);
            free_(sampler);
            return NULL;
        }
        channels[index] = channel;
    }
    Eval eval = eval_create(1.0 / sample_rate);
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
        for (int index = 0; index < sampler->count; index++)
        {
            sampler->eval.wall_time += sampler->eval.wall_tick;
            double output = gen_eval(sampler->channels[index], sampler->eval);
            *(buffer++) = sampler_quantize(output);
        }
    }
}

void sampler_free(Sampler *sampler)
{
    for (int index = 0; index < sampler->count; index++)
    {
        gen_free(sampler->channels[index]);
    }
    free_(sampler->channels);
    sampler->channels = NULL;
    free_(sampler);
}

#endif // CSYNTH_SAMPLER_H

//
// sampler.h - Sampling multiple channels, like stereophonic sound.
//
#ifndef CSYNTH_SAMPLER_H
#define CSYNTH_SAMPLER_H

#include "../core/func.h"
#include "../core/gen.h"
#include "../util/default.h"
#include "../util/error.h"

typedef int16_t sample_t;

typedef struct
{
    Gen **channels;
    int count;
} Sampler;

Sampler *sampler_create(int count, Func **roots, int sample_rate)
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
        Gen *channel = gen_create(roots[index], 1.0 / sample_rate);
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
    *sampler = (Sampler){.channels = channels, .count = count};
    return sampler;
}

void sampler_sample(Sampler *sampler, size_t count, sample_t *buffer)
{
    for (size_t frame = 0; frame < count; frame++)
    {
        for (int index = 0; index < sampler->count; index++)
        {
            double output = gen_eval(sampler->channels[index]);
            double clip = output > 1.0 ? 1.0 : (output < -1.0 ? -1.0 : output);
            *(buffer++) = (sample_t)(clip * 32767);
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

//
// writer.h - Samples a function and writes the result to a WAV file.
//
#ifndef CSYNTH_WRITER_H
#define CSYNTH_WRITER_H

#include <stdio.h>
#include <string.h>

#include "./wav_header.h"

#define WRITER_BUFFER_SIZE 4096

int writer_write_file(int channel_count, Func **roots, double duration, FILE *file)
{
    uint32_t sample_count = duration * SAMPLE_RATE;
    int err = wav_header_write(sample_count, channel_count, file);
    if (err)
    {
        return err;
    }
    Sampler *sampler = sampler_create(channel_count, roots);
    sample_t buffer[WRITER_BUFFER_SIZE];
    uint32_t buffer_samples = WRITER_BUFFER_SIZE / channel_count;
    while (sample_count)
    {
        unsigned long samples = buffer_samples < sample_count ? buffer_samples : sample_count;
        sampler_sample(sampler, samples, buffer);
        size_t count = fwrite(buffer, sizeof(sample_t), channel_count * samples, file);
        if (count != channel_count * samples)
        {
            fprintf(stderr, "Failed to write samples\n");
            sampler_free(sampler);
            return -1;
        }
        sample_count -= samples;
    }
    sampler_free(sampler);
    return 0;
}

int writer_write_channels(int channel_count, Func **roots, double duration, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    int result = writer_write_file(channel_count, roots, duration, file);
    fclose(file);
    return result;
}

int write_file(Func *root, double duration, const char *filename)
{
    return writer_write_channels(1, (Func *[]){root}, duration, filename);
}

int write_file_stereo(Func *left, Func *right, double duration, const char *filename)
{
    return writer_write_channels(2, (Func *[]){left, right}, duration, filename);
}

#endif // CSYNTH_WRITER_H

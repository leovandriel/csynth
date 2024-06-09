//
// writer.h - Samples a function and writes the result to a WAV file.
//
#ifndef CSYNTH_WRITER_H
#define CSYNTH_WRITER_H

#include <stdio.h>
#include <string.h>

#include "../util/cleanup.h"
#include "./wav_header.h"

#define WRITER_BUFFER_SIZE 4096

int writer_write_file_no_cleanup(int channel_count, Func **channels, double duration, FILE *file)
{
    uint32_t sample_count = (uint32_t)(duration * SAMPLE_RATE);
    int err = wav_header_write(sample_count, channel_count, file);
    if (err)
    {
        return err;
    }
    Sampler *sampler = sampler_create(channel_count, channels);
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

int writer_write_file(int count, Func **channels, double duration, FILE *file)
{
    int err = writer_write_file_no_cleanup(count, channels, duration, file);
    cleanup_all();
    return err;
}

int writer_write_channels(int channel_count, Func **channels, double duration, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    int result = writer_write_file(channel_count, channels, duration, file);
    fclose(file);
    return result;
}

int write(Func *input, double duration, const char *filename)
{
    return writer_write_channels(1, (Func *[]){input}, duration, filename);
}

int write_(Func *input, double duration) { return write(input, duration, CONFIG_DEFAULT_WAV_FILENAME); }

int write_stereo(Func *left, Func *right, double duration, const char *filename)
{
    return writer_write_channels(2, (Func *[]){left, right}, duration, filename);
}

int write_mono(Func *input, double duration, const char *filename) { return write(input, duration, filename); }

#endif // CSYNTH_WRITER_H

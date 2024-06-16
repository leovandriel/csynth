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

csError writer_write_channels_no_cleanup(int channel_count, Func **channels, double duration, FILE *file, int sample_rate)
{
    uint32_t sample_count = (uint32_t)(duration * sample_rate + 0.5);
    csError error = wav_header_write(sample_count, channel_count, file, sample_rate);
    if (error != csErrorNone)
    {
        return error;
    }
    Sampler *sampler = sampler_create(channel_count, channels, sample_rate);
    sample_t buffer[WRITER_BUFFER_SIZE];
    uint32_t buffer_samples = WRITER_BUFFER_SIZE / channel_count;
    while (sample_count)
    {
        unsigned long samples = buffer_samples < sample_count ? buffer_samples : sample_count;
        sampler_sample(sampler, samples, buffer);
        size_t count = fwrite(buffer, sizeof(sample_t), channel_count * samples, file);
        if (count != channel_count * samples)
        {
            sampler_free(sampler);
            return error_type(csErrorFileWrite);
        }
        sample_count -= samples;
    }
    sampler_free(sampler);
    return csErrorNone;
}

csError writer_write_channels(int count, Func **channels, double duration, FILE *file, int sample_rate)
{
    csError error = writer_write_channels_no_cleanup(count, channels, duration, file, sample_rate);
    cleanup_all();
    return error;
}

csError writer_write_file(int channel_count, Func **channels, double duration, const char *filename, int sample_rate)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        return error_type_message(csErrorFileOpen, "Unable to open file: %s", filename);
    }
    csError error = writer_write_channels(channel_count, channels, duration, file, sample_rate);
    if (error != csErrorNone)
    {
        fclose(file);
        return error;
    }
    if (fclose(file) == EOF)
    {
        return error_type(csErrorFileClose);
    }
    return csErrorNone;
}

csError write(Func *input, double duration, const char *filename)
{
    return writer_write_file(1, (Func *[]){input}, duration, filename, CONFIG_DEFAULT_SAMPLE_RATE);
}

csError write_(Func *input, double duration) { return write(input, duration, CONFIG_DEFAULT_WAV_FILENAME); }

csError write_stereo(Func *left, Func *right, double duration, const char *filename)
{
    return writer_write_file(2, (Func *[]){left, right}, duration, filename, CONFIG_DEFAULT_SAMPLE_RATE);
}

csError write_mono(Func *input, double duration, const char *filename) { return write(input, duration, filename); }

#endif // CSYNTH_WRITER_H

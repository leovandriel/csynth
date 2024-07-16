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

csError writer_write_channels_no_cleanup(double duration, FILE *file, size_t sample_rate, size_t channel_count, Func **channels)
{
    uint32_t sample_count = (uint32_t)(duration * (double)sample_rate + 0.5);
    csError error = wav_header_write(sample_count, (uint32_t)channel_count, file, sample_rate);
    if (error != csErrorNone)
    {
        return error;
    }
    Sampler *sampler = sampler_create(sample_rate, channel_count, channels);
    sample_t buffer[WRITER_BUFFER_SIZE];
    uint32_t buffer_samples = WRITER_BUFFER_SIZE / channel_count;
    while (sample_count)
    {
        size_t samples = buffer_samples < sample_count ? buffer_samples : sample_count;
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

csError writer_write_channels(double duration, FILE *file, size_t sample_rate, size_t count, Func **channels)
{
    csError error = writer_write_channels_no_cleanup(duration, file, sample_rate, count, channels);
    cleanup_all();
    return error;
}

csError writer_write_file(double duration, const char *filename, size_t sample_rate, size_t channel_count, Func **channels)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        return error_type_message(csErrorFileOpen, "Unable to open file: %s", filename);
    }
    csError error = writer_write_channels(duration, file, sample_rate, channel_count, channels);
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

csError write_channels(double duration, const char *filename, size_t count, Func **channels) { return writer_write_file(duration, filename, SAMPLE_RATE, count, channels); } /* writer_ */
csError write(double duration, const char *filename, Func *input) { return write_channels(duration, filename, ARGS(input)); }                                                /* writer_ */
csError write_(double duration, Func *input) { return write(duration, DEFAULT_WAV_FILENAME, input); }                                                                        /* writer_ */
csError write_stereo(double duration, const char *filename, Func *left, Func *right) { return write_channels(duration, filename, ARGS(left, right)); }                       /* writer_ */

#endif // CSYNTH_WRITER_H

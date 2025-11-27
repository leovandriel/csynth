#ifndef CSYNTH_READER_H
#define CSYNTH_READER_H

#include <stdio.h>
#include <string.h>

#include "./file.h"
#include "./wav_header.h"

/**
 * @brief PCM samples.
 */
typedef struct
{
    /** @brief PCM sample data. */
    sample_t *samples;
    /** @brief Number of samples. */
    size_t sample_count;
    /** @brief Number of channels. */
    size_t channel_count;
    /** @brief Sample rate, e.g. 44100. */
    size_t sample_rate;
} PcmBuffer;

/**
 * @brief Read samples from a WAV file.
 *
 * @param samples Sample data buffer.
 * @param file File handle to read from.
 * @return csError Error code, zero on success.
 */
csError reader_read_file(PcmBuffer *buffer, FILE *file)
{
    WavHeader header = {0};
    csError error = wav_header_read_file(&header, file);
    if (error != csErrorNone)
    {
        return error;
    }
    error = wav_header_parse(&header, &buffer->sample_count, &buffer->channel_count, &buffer->sample_rate);
    if (error != csErrorNone)
    {
        return error;
    }
    size_t count = buffer->sample_count * buffer->channel_count;
    sample_t *samples = (sample_t *)malloc_(count * sizeof(sample_t));
    if (samples == NULL)
    {
        return error_type(csErrorMemoryAlloc);
    }
    size_t sample_count = fread(samples, sizeof(sample_t), count, file);
    if (sample_count != count)
    {
        free_(samples);
        return error_type(csErrorFileRead);
    }
    buffer->samples = samples;
    return csErrorNone;
}

sample_t reader_sample(PcmBuffer *buffer, double time, int channel)
{
    uint32_t index = (uint32_t)(time * (double)buffer->sample_rate + 0.5);
    if (index >= buffer->sample_count)
    {
        return 0;
    }
    return buffer->samples[index * buffer->channel_count + channel];
}

void reader_free(PcmBuffer *buffer)
{
    free_(buffer->samples);
}

csError reader_read_filename(PcmBuffer *buffer, const char *filename)
{
    FILE *file = fopen_(filename, "rb");
    if (file == NULL)
    {
        return error_type_message(csErrorFileOpen, "Unable to open file: %s", filename);
    }
    csError error = reader_read_file(buffer, file);
    if (error != csErrorNone)
    {
        fclose_(file);
        return error;
    }
    if (fclose_(file) == EOF)
    {
        return error_type(csErrorFileClose);
    }
    return csErrorNone;
}

#endif // CSYNTH_READER_H

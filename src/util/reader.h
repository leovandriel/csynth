//
// reader.h - Reads sample data from WAV file.
//
#ifndef CSYNTH_READER_H
#define CSYNTH_READER_H

#include <string.h>
#include <stdio.h>

#include "./sampler.h"
#include "./wav_header.h"

typedef struct
{
    sample_t *buffer;
    size_t sample_count;
    int channel_count;
    double duration;
} ReaderSamples;

typedef int (*reader_callback)(size_t size, void *buffer, void *context);

int reader_read_callback(ReaderSamples *samples, reader_callback callback, void *context)
{
    WavHeader header = {0};
    int err = callback(sizeof(header), &header, context);
    if (err)
    {
        fprintf(stderr, "Unable to read WAV header\n");
        return err;
    }
    if (memcmp(header.riff_type, "RIFF", 4) || memcmp(header.file_type, "WAVE", 4) || memcmp(header.format_mark, "fmt ", 4) || header.format_type != 1 || memcmp(header.data_chunk, "data", 4))
    {
        fprintf(stderr, "Unsupported WAV format\n");
        return -1;
    }
    if (header.format_size != WAV_HEADER_FORMAT_SIZE)
    {
        fprintf(stderr, "Unsupported WAV format size: %d\n", header.format_size);
        return -1;
    }
    if (header.sample_rate != SAMPLER_RATE)
    {
        fprintf(stderr, "Unsupported WAV sample rate: %d\n", header.sample_rate);
        return -1;
    }
    if (header.file_size - header.data_size != WAV_HEADER_SIZE)
    {
        fprintf(stderr, "Unsupported WAV header size: %d\n", header.file_size - header.data_size);
        return -1;
    }
    if (header.byte_rate != sizeof(sample_t) * header.num_channels * SAMPLER_RATE || header.block_align != sizeof(sample_t) * header.num_channels || header.bits_sample != sizeof(sample_t) * 8)
    {
        fprintf(stderr, "Unsupported WAV sample bits: %d\n", header.bits_sample);
        return -1;
    }
    int channel_count = header.num_channels;
    uint32_t data_size = header.data_size;
    uint32_t sample_count = data_size / (sizeof(sample_t) * channel_count);
    double duration = sample_count / SAMPLER_RATE;
    sample_t *buffer = (sample_t *)calloc(sample_count * channel_count, sizeof(sample_t));
    err = callback(sample_count * channel_count * sizeof(sample_t), buffer, context);
    if (err)
    {
        fprintf(stderr, "Unable to read WAV data\n");
        free(buffer);
        return err;
    }
    samples->buffer = buffer;
    samples->sample_count = sample_count;
    samples->channel_count = channel_count;
    samples->duration = duration;
    return 0;
}

sample_t reader_sample(ReaderSamples *samples, double time, int channel)
{
    uint32_t index = (uint32_t)(time * SAMPLER_RATE + 0.5);
    if (index >= samples->sample_count)
    {
        return 0.0;
    }
    return samples->buffer[index * samples->channel_count + channel];
}

void reader_free(ReaderSamples *samples)
{
    free(samples->buffer);
}

int reader_file_callback(size_t size, void *buffer, void *context)
{
    fread(buffer, size, 1, (FILE *)context);
    return 0;
}

int reader_read_file(ReaderSamples *samples, const char *filename)
{
    FILE *file = fopen(filename, "rb");
    int result = reader_read_callback(samples, reader_file_callback, file);
    fclose(file);
    return result;
}

#endif // CSYNTH_READER_H

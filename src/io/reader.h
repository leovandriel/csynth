//
// reader.h - Reads sample data from WAV file.
//
#ifndef CSYNTH_READER_H
#define CSYNTH_READER_H

#include <stdio.h>
#include <string.h>

#include "../util/config.h"
#include "./wav_header.h"

typedef struct
{
    sample_t *buffer;
    size_t sample_count;
    int channel_count;
    double duration;
    uint32_t sample_rate;
} ReaderSamples;

int reader_read_file(ReaderSamples *samples, FILE *file)
{
    WavHeader header = {0};
    size_t count = fread(&header, sizeof(header), 1, file);
    if (count != 1)
    {
        fprintf(stderr, "Unable to read WAV header\n");
        return -1;
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
    if (header.file_size - header.data_size != WAV_HEADER_SIZE)
    {
        fprintf(stderr, "Unsupported WAV header size: %d\n", header.file_size - header.data_size);
        return -1;
    }
    if (header.byte_rate != sizeof(sample_t) * header.num_channels * header.sample_rate || header.block_align != sizeof(sample_t) * header.num_channels || header.bits_sample != sizeof(sample_t) * 8)
    {
        fprintf(stderr, "Unsupported WAV sample bits: %d\n", header.bits_sample);
        return -1;
    }
    int channel_count = header.num_channels;
    uint32_t data_size = header.data_size;
    uint32_t sample_count = data_size / (sizeof(sample_t) * channel_count);
    double duration = sample_count / header.sample_rate;
    sample_t *buffer = (sample_t *)calloc_(sample_count * channel_count, sizeof(sample_t));
    count = fread(buffer, sizeof(sample_t), sample_count * channel_count, file);
    if (count != sample_count * channel_count)
    {
        fprintf(stderr, "Unable to read WAV data\n");
        free_(buffer);
        return -1;
    }
    samples->buffer = buffer;
    samples->sample_count = sample_count;
    samples->channel_count = channel_count;
    samples->duration = duration;
    samples->sample_rate = header.sample_rate;
    free_(buffer);
    return 0;
}

sample_t reader_sample(ReaderSamples *samples, double time, int channel)
{
    uint32_t index = (uint32_t)(time * samples->sample_rate + 0.5);
    if (index >= samples->sample_count)
    {
        return 0;
    }
    return samples->buffer[index * samples->channel_count + channel];
}

void reader_free(ReaderSamples *samples)
{
    free_(samples->buffer);
}

int reader_read_filename(ReaderSamples *samples, const char *filename)
{
    FILE *file = fopen(filename, "rb");
    int result = reader_read_file(samples, file);
    fclose(file);
    return result;
}

#endif // CSYNTH_READER_H

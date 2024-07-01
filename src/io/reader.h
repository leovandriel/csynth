//
// reader.h - Reads sample data from WAV file.
//
#ifndef CSYNTH_READER_H
#define CSYNTH_READER_H

#include <stdio.h>
#include <string.h>

#include "./wav_header.h"

typedef struct
{
    sample_t *buffer;
    size_t sample_count;
    int channel_count;
    double duration;
    uint32_t sample_rate;
} ReaderSamples;

csError reader_read_file(ReaderSamples *samples, FILE *file)
{
    WavHeader header = {0};
    size_t count = fread(&header, sizeof(header), 1, file);
    if (count != 1)
    {
        return error_type_message(csErrorWav, "Unable to read WAV header");
    }
    if (memcmp(header.riff_type, "RIFF", 4) || memcmp(header.file_type, "WAVE", 4) || memcmp(header.format_mark, "fmt ", 4) || header.format_type != 1 || memcmp(header.data_chunk, "data", 4))
    {
        return error_type_message(csErrorWav, "Unsupported WAV format");
    }
    if (header.format_size != WAV_HEADER_FORMAT_SIZE)
    {
        return error_type_message(csErrorWav, "Unsupported WAV format size: %d", header.format_size);
    }
    if (header.file_size - header.data_size != WAV_HEADER_SIZE)
    {
        return error_type_message(csErrorWav, "Unsupported WAV header size: %d", header.file_size - header.data_size);
    }
    if (header.byte_rate != sizeof(sample_t) * header.num_channels * header.sample_rate || header.block_align != sizeof(sample_t) * header.num_channels || header.bits_sample != sizeof(sample_t) * 8)
    {
        return error_type_message(csErrorWav, "Unsupported WAV sample bits: %d", header.bits_sample);
    }
    int channel_count = header.num_channels;
    uint32_t data_size = header.data_size;
    uint32_t sample_count = data_size / (sizeof(sample_t) * channel_count);
    double duration = sample_count / header.sample_rate;
    sample_t *buffer = (sample_t *)malloc_(sample_count * channel_count * sizeof(sample_t));
    if (buffer == NULL)
    {
        return error_type(csErrorMemoryAlloc);
    }
    count = fread(buffer, sizeof(sample_t), sample_count * channel_count, file);
    if (count != sample_count * channel_count)
    {
        free_(buffer);
        return error_type(csErrorFileRead);
    }
    samples->buffer = buffer;
    samples->sample_count = sample_count;
    samples->channel_count = channel_count;
    samples->duration = duration;
    samples->sample_rate = header.sample_rate;
    free_(buffer);
    return csErrorNone;
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

csError reader_read_filename(ReaderSamples *samples, const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        return error_type_message(csErrorFileOpen, "Unable to open file: %s", filename);
    }
    csError error = reader_read_file(samples, file);
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

#endif // CSYNTH_READER_H

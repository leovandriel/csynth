//
// writer.h - Samples a function and writes the result to a WAV file.
//
#ifndef CSYNTH_WRITER_H
#define CSYNTH_WRITER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "./sampler.h"

static const int WRITER_BUFFER_SIZE = 4096;

typedef struct
{
    char riff_type[4];
    uint32_t file_size;
    char file_type[4];
    char format_mark[4];
    uint32_t format_size;
    uint16_t format_type;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_sample;
    char data_chunk[4];
    uint32_t data_size;
} FileHeader;

#define FH_SIZE(field) (sizeof((FileHeader){0}.field))
static const size_t WRITER_HEADER_SIZE = sizeof(FileHeader) - FH_SIZE(riff_type) - FH_SIZE(file_size);
static const size_t WRITER_FORMAT_SIZE = FH_SIZE(format_type) + FH_SIZE(num_channels) + FH_SIZE(sample_rate) + FH_SIZE(byte_rate) + FH_SIZE(block_align) + FH_SIZE(bits_sample);

int write_array(int count, Func **roots, double duration, FILE *file)
{
    uint32_t sample_count = duration * SAMPLER_RATE;
    uint32_t data_size = sizeof(sample_t) * count * sample_count;
    FileHeader header = {0};
    memcpy(header.riff_type, "RIFF", 4);
    header.file_size = WRITER_HEADER_SIZE + data_size;
    memcpy(header.file_type, "WAVE", 4);
    memcpy(header.format_mark, "fmt ", 4);
    header.format_size = WRITER_FORMAT_SIZE;
    header.format_type = 1; // PCM
    header.num_channels = count;
    header.sample_rate = SAMPLER_RATE;
    header.byte_rate = sizeof(sample_t) * count * SAMPLER_RATE;
    header.block_align = sizeof(sample_t) * count;
    header.bits_sample = sizeof(sample_t) * 8;
    memcpy(header.data_chunk, "data", 4);
    header.data_size = data_size;
    fwrite(&header, sizeof(header), 1, file);
    Sampler *sampler = sampler_create(count, roots);
    sample_t buffer[WRITER_BUFFER_SIZE];
    uint32_t buffer_samples = WRITER_BUFFER_SIZE / count;
    while (sample_count)
    {
        unsigned long samples = buffer_samples < sample_count ? buffer_samples : sample_count;
        sampler_sample(sampler, samples, buffer);
        fwrite(buffer, sizeof(sample_t), samples * count, file);
        sample_count -= samples;
    }
    sampler_free(sampler);
    return 0;
}

int write(Func *root, double duration, FILE *file)
{
    return write_array(1, (Func *[]){root}, duration, file);
}

int write_stereo(Func *left, Func *right, double duration, FILE *file)
{
    return write_array(2, (Func *[]){left, right}, duration, file);
}

int write_file_array(int count, Func **roots, double duration, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    int result = write_array(count, roots, duration, file);
    fclose(file);
    return result;
}

int write_file(Func *root, double duration, const char *filename)
{
    return write_file_array(1, (Func *[]){root}, duration, filename);
}

int write_file_stereo(Func *left, Func *right, double duration, const char *filename)
{
    return write_file_array(2, (Func *[]){left, right}, duration, filename);
}

#endif // CSYNTH_WRITER_H

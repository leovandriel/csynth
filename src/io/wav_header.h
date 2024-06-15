//
// wav_header.h - WAV format
//
#ifndef CSYNTH_WAV_HEADER_H
#define CSYNTH_WAV_HEADER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "./sampler.h"

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
} WavHeader;

#define WAV_HEADER_(field) (sizeof((WavHeader){0}.field))
static const size_t WAV_HEADER_SIZE = sizeof(WavHeader) - WAV_HEADER_(riff_type) - WAV_HEADER_(file_size);
static const size_t WAV_HEADER_FORMAT_SIZE = WAV_HEADER_(format_type) + WAV_HEADER_(num_channels) + WAV_HEADER_(sample_rate) + WAV_HEADER_(byte_rate) + WAV_HEADER_(block_align) + WAV_HEADER_(bits_sample);

int wav_header_write(uint32_t sample_count, uint32_t channel_count, FILE *file, int sample_rate)
{
    uint32_t data_size = sizeof(sample_t) * channel_count * sample_count;
    WavHeader header = {0};
    memcpy(header.riff_type, "RIFF", 4);
    header.file_size = WAV_HEADER_SIZE + data_size;
    memcpy(header.file_type, "WAVE", 4);
    memcpy(header.format_mark, "fmt ", 4);
    header.format_size = WAV_HEADER_FORMAT_SIZE;
    header.format_type = 1; // PCM
    header.num_channels = channel_count;
    header.sample_rate = sample_rate;
    header.byte_rate = sizeof(sample_t) * channel_count * sample_rate;
    header.block_align = sizeof(sample_t) * channel_count;
    header.bits_sample = sizeof(sample_t) * 8;
    memcpy(header.data_chunk, "data", 4);
    header.data_size = data_size;
    size_t count = fwrite(&header, sizeof(header), 1, file);
    if (count != 1)
    {
        fprintf(stderr, "Failed to write header\n");
        return -1;
    }
    return 0;
}

#endif // CSYNTH_WAV_HEADER_H

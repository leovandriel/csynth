//
// wav_header.h - WAV format
//
#ifndef CSYNTH_WAV_HEADER_H
#define CSYNTH_WAV_HEADER_H

#include <stdlib.h>
#include <stdint.h>

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

#endif // CSYNTH_WAV_HEADER_H

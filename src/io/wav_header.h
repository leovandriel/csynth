#ifndef CSYNTH_WAV_HEADER_H
#define CSYNTH_WAV_HEADER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "./file.h"
#include "./sampler.h"

#define DEFAULT_WAV_FILENAME "output/default.wav"

/**
 * @brief WAV header structure, written verbatim to the file.
 */
typedef struct
{
    /** @brief RIFF header, containing "RIFF". */
    char riff_type[4];
    /** @brief Size of the file in bytes. */
    uint32_t file_size;
    /** @brief File type, containing "WAVE". */
    char file_type[4];
    /** @brief Format mark, containing "fmt ". */
    char format_mark[4];
    /** @brief Size of the format chunk. */
    uint32_t format_size;
    /** @brief Format type, 1 (PCM) */
    uint16_t format_type;
    /** @brief Number of channels, e.g. two for stereo */
    uint16_t num_channels;
    /** @brief Sample rate, e.g. 44100. */
    uint32_t sample_rate;
    /** @brief Byte rate, i.e. sample_rate x num_channels x sizeof(sample_t) */
    uint32_t byte_rate;
    /** @brief Block align, num_channels x sizeof(sample_t) */
    uint16_t block_align;
    /** @brief Bits per sample. */
    uint16_t bits_sample;
    /** @brief Data chunk, containing "data" */
    char data_chunk[4];
    /** @brief Size of the data chunk, channel_count * sample_count x
     * sizeof(sample_t) */
    uint32_t data_size;
} WavHeader;

#define WAV_HEADER_(field) (sizeof((WavHeader){0}.field))
static const size_t WAV_HEADER_SIZE = sizeof(WavHeader) - WAV_HEADER_(riff_type) - WAV_HEADER_(file_size);
static const size_t WAV_HEADER_FORMAT_SIZE = WAV_HEADER_(format_type) + WAV_HEADER_(num_channels) + WAV_HEADER_(sample_rate) + WAV_HEADER_(byte_rate) + WAV_HEADER_(block_align) + WAV_HEADER_(bits_sample);

csError wav_header_read_file(WavHeader *header, FILE *file)
{
    size_t header_count = fread(header, sizeof(*header), 1, file);
    if (header_count != 1)
    {
        return error_type_message(csErrorWav, "Unable to read WAV header");
    }
    return csErrorNone;
}

csError wav_header_write_file(WavHeader *header, FILE *file)
{
    size_t header_count = fwrite(header, sizeof(*header), 1, file);
    if (header_count != 1)
    {
        return error_type_message(csErrorWav, "Unable to write WAV header");
    }
    return csErrorNone;
}

csError wav_header_parse(WavHeader *header, size_t *sample_count, size_t *channel_count, size_t *sample_rate)
{
    if (memcmp(header->riff_type, "RIFF", 4) || memcmp(header->file_type, "WAVE", 4) || memcmp(header->format_mark, "fmt ", 4) || header->format_type != 1 || memcmp(header->data_chunk, "data", 4))
    {
        return error_type_message(csErrorWav, "Unsupported WAV format");
    }
    if (header->format_size != WAV_HEADER_FORMAT_SIZE)
    {
        return error_type_message(csErrorWav, "Unsupported WAV format size: %d", header->format_size);
    }
    if (header->file_size - header->data_size != WAV_HEADER_SIZE)
    {
        return error_type_message(csErrorWav, "Unsupported WAV header size: %d", header->file_size - header->data_size);
    }
    if (header->byte_rate != sizeof(sample_t) * header->num_channels * header->sample_rate || header->block_align != sizeof(sample_t) * header->num_channels || header->bits_sample != sizeof(sample_t) * 8)
    {
        return error_type_message(csErrorWav, "Unsupported WAV sample bits: %d", header->bits_sample);
    }
    *sample_count = header->data_size / (sizeof(sample_t) * header->num_channels);
    *channel_count = header->num_channels;
    *sample_rate = header->sample_rate;
    return csErrorNone;
}

void wav_header_update(WavHeader *header, size_t sample_count, size_t channel_count, size_t sample_rate)
{
    uint32_t data_size = sizeof(sample_t) * channel_count * sample_count;
    memcpy(header->riff_type, "RIFF", 4);
    header->file_size = WAV_HEADER_SIZE + data_size;
    memcpy(header->file_type, "WAVE", 4);
    memcpy(header->format_mark, "fmt ", 4);
    header->format_size = WAV_HEADER_FORMAT_SIZE;
    header->format_type = 1; // PCM
    header->num_channels = channel_count;
    header->sample_rate = (uint32_t)sample_rate;
    header->byte_rate = (uint32_t)(sizeof(sample_t) * channel_count * sample_rate);
    header->block_align = (uint16_t)(sizeof(sample_t) * channel_count);
    header->bits_sample = (uint16_t)(sizeof(sample_t) * 8);
    memcpy(header->data_chunk, "data", 4);
    header->data_size = data_size;
}

csError wav_header_read_filename(WavHeader *header, const char *filename)
{
    FILE *file = fopen_(filename, "rb");
    if (file == NULL)
    {
        return error_type_message(csErrorFileOpen, "Unable to open file: %s", filename);
    }
    csError error = wav_header_read_file(header, file);
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

csError wav_header_write_filename(WavHeader *header, const char *filename)
{
    FILE *file = fopen_(filename, "wb");
    if (file == NULL)
    {
        return error_type_message(csErrorFileOpen, "Unable to open file: %s", filename);
    }
    csError error = wav_header_write_file(header, file);
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

#endif // CSYNTH_WAV_HEADER_H

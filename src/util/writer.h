//
// writer.h - Samples a function and writes the result to a WAV file.
//
#ifndef CSYNTH_WRITER_H
#define CSYNTH_WRITER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "../core/func.h"
#include "../core/gen.h"

static const int SAMPLE_RATE = 44100;
static const int OUTPUT_CHANNELS = 1;
static const int BITS_SAMPLE = 16;
static const int BUFFER_SIZE = 4096;

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

void write(Func *root, double duration, FILE *file)
{
    size_t count = duration * SAMPLE_RATE;
    FileHeader header = {0};
    memcpy(header.riff_type, "RIFF", 4);
    header.file_size = count * BITS_SAMPLE * OUTPUT_CHANNELS / 8 + (sizeof(header) - 8);
    memcpy(header.file_type, "WAVE", 4);
    memcpy(header.format_mark, "fmt ", 4);
    header.format_size = 16;
    header.format_type = 1;
    header.num_channels = OUTPUT_CHANNELS;
    header.sample_rate = SAMPLE_RATE;
    header.byte_rate = SAMPLE_RATE * BITS_SAMPLE * OUTPUT_CHANNELS / 8;
    header.block_align = BITS_SAMPLE * OUTPUT_CHANNELS / 8;
    header.bits_sample = BITS_SAMPLE;
    memcpy(header.data_chunk, "data", 4);
    header.data_size = count * BITS_SAMPLE * OUTPUT_CHANNELS / 8;
    fwrite(&header, sizeof(header), 1, file);
    Gen *gen = gen_create(root, 1.0 / SAMPLE_RATE);
    int16_t buffer[BUFFER_SIZE];
    int i = 0;
    for (size_t index = 0; index < count; index++)
    {
        double output = gen_eval(gen);
        double clip = output > 1.0 ? 1.0 : (output < -1.0 ? -1.0 : output);
        buffer[i++] = clip * 32767;
        if (i == BUFFER_SIZE)
        {
            fwrite(buffer, sizeof(uint16_t), BUFFER_SIZE, file);
            i = 0;
        }
    }
    if (i > 0)
    {
        fwrite(buffer, sizeof(uint16_t), i, file);
    }
    gen_free(gen);
}

void write_file(Func *root, double duration, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    write(root, duration, file);
    fclose(file);
}

void write_stdout(Func *root, double duration)
{
    write(root, duration, stdout);
}

#endif // CSYNTH_WRITER_H

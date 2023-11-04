#ifndef COMPOSER_WRITER_H
#define COMPOSER_WRITER_H

#include <stdlib.h>
#include <string.h>

#include "func.h"

#define SAMPLE_RATE 44100
#define OUTPUT_CHANNELS 1
#define BITS_SAMPLE 16
#define BUFFER_SIZE 4096

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

void write_file(Func *root, double duration, const char *filename)
{
    size_t count = duration * SAMPLE_RATE;
    FileHeader header = {0};
    strncpy(header.riff_type, "RIFF", 4);
    header.file_size = count * BITS_SAMPLE * OUTPUT_CHANNELS / 8 + (sizeof(header) - 8);
    strncpy(header.file_type, "WAVE", 4);
    strncpy(header.format_mark, "fmt ", 4);
    header.format_size = 16;
    header.format_type = 1;
    header.num_channels = OUTPUT_CHANNELS;
    header.sample_rate = SAMPLE_RATE;
    header.byte_rate = SAMPLE_RATE * BITS_SAMPLE * OUTPUT_CHANNELS / 8;
    header.block_align = BITS_SAMPLE * OUTPUT_CHANNELS / 8;
    header.bits_sample = BITS_SAMPLE;
    strncpy(header.data_chunk, "data", 4);
    header.data_size = count * BITS_SAMPLE * OUTPUT_CHANNELS / 8;
    FILE *file = fopen(filename, "wb");
    fwrite(&header, sizeof(header), 1, file);
    func_init(root, SAMPLE_RATE);
    int16_t buffer[BUFFER_SIZE];
    int i = 0;
    for (size_t index = 0; index < count; index++)
    {
        double output = func_eval(root, index, SAMPLE_RATE);
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
    func_free(root);
    fclose(file);
}

void write(Func *root, double duration)
{
    write_file(root, duration, "output/default.wav");
}

#endif // COMPOSER_WRITER_H

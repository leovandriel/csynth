#ifndef CSYNTH_PPM_HEADER_H
#define CSYNTH_PPM_HEADER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../util/error.h"
#include "./file.h"

csError ppm_header_write(FILE *file, size_t width, size_t height)
{
    if (fprintf(file, "P6\n%zu %zu\n255\n", width, height) < 0)
    {
        return error_type_message(csErrorFileWrite, "Unable to write PPM header");
    }
    return csErrorNone;
}

void ppm_bgra_to_rgb(unsigned char *buffer, size_t width, size_t height)
{
    for (size_t i = 0; i < width * height; i++)
    {
        buffer[i * 3 + 0] = buffer[i * 4 + 2];
        buffer[i * 3 + 1] = buffer[i * 4 + 1];
        buffer[i * 3 + 2] = buffer[i * 4 + 0];
    }
}

csError ppm_write_file(FILE *file, size_t width, size_t height, unsigned char *buffer)
{
    csError error = ppm_header_write(file, width, height);
    if (error != csErrorNone)
    {
        return error;
    }
    size_t size = width * height * 3;
    size_t count = fwrite(buffer, sizeof(unsigned char), size, file);
    if (count != size)
    {
        return error_type_message(csErrorFileWrite, "Unable to write PPM data");
    }
    return csErrorNone;
}

csError ppm_write_filename(const char *filename, size_t width, size_t height, unsigned char *buffer)
{
    FILE *file = fopen_(filename, "wb");
    if (file == NULL)
    {
        return error_type_message(csErrorFileOpen, "Unable to open file: %s", filename);
    }
    csError error = ppm_write_file(file, width, height, buffer);
    if (error != csErrorNone)
    {
        fclose_(file);
        return error;
    }
    if (fclose_(file) == EOF)
    {
        return error_type_message(csErrorFileClose, "Unable to close file: %s", filename);
    }
    return csErrorNone;
}

#endif // CSYNTH_PPM_HEADER_H

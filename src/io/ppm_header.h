#ifndef CSYNTH_PPM_HEADER_H
#define CSYNTH_PPM_HEADER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void ppm_header_write(FILE *file, size_t width, size_t height)
{
    fprintf(file, "P6\n%zu %zu\n255\n", width, height);
}

#endif // CSYNTH_PPM_HEADER_H

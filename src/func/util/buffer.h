//
// buffer.h - A (cyclic) sample buffer
//
#ifndef CSYNTH_BUFFER_H
#define CSYNTH_BUFFER_H

#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    double *samples;
    unsigned long size;
    unsigned long max;
} Buffer;

void buffer_init(Buffer *buffer, unsigned long size)
{
    buffer->samples = (double *)calloc(size, sizeof(double));
    buffer->size = size;
}

void buffer_resize(Buffer *buffer, unsigned long size, double (*fill)(void))
{
    if (buffer->samples == NULL)
    {
        buffer->samples = size > 0 ? (double *)calloc(size, sizeof(double)) : NULL;
        if (fill != NULL)
        {
            for (unsigned long i = 0; i < size; i++)
            {
                buffer->samples[i] = fill();
            }
        }
        buffer->max = size;
    }
    else if (size > buffer->max)
    {
        unsigned long max = size * 2;
        buffer->samples = (double *)realloc(buffer->samples, max * sizeof(double));
        if (fill != NULL)
        {
            for (unsigned long i = buffer->max; i < max - buffer->max; i++)
            {
                buffer->samples[i] = fill();
            }
        }
        else
        {
            memset(buffer->samples + buffer->max, 0, (max - buffer->max) * sizeof(double));
        }
        // TODO: shift the contents of the buffer
        buffer->max = max;
    }
    buffer->size = size;
}

void buffer_free(Buffer *buffer)
{
    free(buffer->samples);
}

void test_buffer()
{
}

#endif // CSYNTH_BUFFER_H

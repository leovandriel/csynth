//
// buffer.h - A (cyclic) sample buffer with dynamic resizing.
//
#ifndef CSYNTH_BUFFER_H
#define CSYNTH_BUFFER_H

#include <stdlib.h>
#include <string.h>

#include "../util/error.h"
#include "../util/rand.h"

typedef struct
{
    double *samples;
    unsigned long size;
    unsigned long capacity;
} Buffer;

csError buffer_init(Buffer *buffer, unsigned long size)
{
    double *samples = NULL;
    if (size > 0)
    {
        samples = (double *)calloc_(size, sizeof(double));
        if (samples == NULL)
        {
            return error_type(csErrorMemoryAlloc);
        }
    }
    buffer->samples = samples;
    buffer->capacity = size;
    buffer->size = size;
    return csErrorNone;
}

static unsigned long buffer_resize_from_zero(Buffer *buffer, unsigned long size, double (*fill)(unsigned long))
{
    double *samples = (double *)malloc_(size * sizeof(double));
    if (samples == NULL)
    {
        error_catch(csErrorMemoryAlloc);
        // TODO(leo): handle error
        return 0;
    }
    if (fill != NULL)
    {
        for (unsigned long i = 0; i < size; i++)
        {
            samples[i] = fill(i);
        }
    }
    else
    {
        memset(samples, 0, size * sizeof(double));
    }
    buffer->samples = samples;
    buffer->capacity = size;
    buffer->size = size;
    return 0;
}

static unsigned long buffer_resize_to_zero(Buffer *buffer)
{
    free_(buffer->samples);
    buffer->samples = NULL;
    buffer->capacity = 0;
    buffer->size = 0;
    return 0;
}

static unsigned long buffer_resize_up(Buffer *buffer, unsigned long size, unsigned long index, double (*fill)(unsigned long))
{
    if (size > buffer->capacity)
    {
        unsigned long capacity = size * 2;
        double *samples = (double *)realloc_(buffer->samples, capacity * sizeof(double));
        if (samples == NULL)
        {
            error_catch(csErrorMemoryAlloc);
            return index;
        }
        buffer->capacity = capacity;
        buffer->samples = samples;
    }
    unsigned long diff = size - buffer->size;
    unsigned long too = index + diff;
    memmove(buffer->samples + too, buffer->samples + index, diff * sizeof(double));
    if (fill != NULL)
    {
        for (unsigned long i = index, end = index + diff; i < end; i++)
        {
            buffer->samples[i] = fill(i);
        }
    }
    else
    {
        memset(buffer->samples + index, 0, diff * sizeof(double));
    }
    buffer->size = size;
    return index;
}

static unsigned long buffer_resize_down(Buffer *buffer, unsigned long size, unsigned long index)
{
    if (index < size)
    {
        unsigned long diff = size - index;
        unsigned long from = buffer->size - diff;
        memmove(buffer->samples + index, buffer->samples + from, diff * sizeof(double));
    }
    else if (index > size)
    {
        unsigned long diff = index - size;
        unsigned long from = index - 1;
        memmove(buffer->samples, buffer->samples + from, diff * sizeof(double));
        index -= size;
    }
    else
    {
        index = 0;
    }
    buffer->size = size;
    return index;
}

unsigned long buffer_resize(Buffer *buffer, unsigned long size, unsigned long index, double (*fill)(unsigned long))
{
    if (size != buffer->size)
    {
        if (buffer->size == 0)
        {
            return buffer_resize_from_zero(buffer, size, fill);
        }
        if (size == 0)
        {
            return buffer_resize_to_zero(buffer);
        }
        if (size > buffer->size)
        {
            return buffer_resize_up(buffer, size, index, fill);
        }
        if (size < buffer->size)
        {
            return buffer_resize_down(buffer, size, index);
        }
    }
    return index;
}

void buffer_free(Buffer *buffer)
{
    free_(buffer->samples);
}

double fill_rand_0_1(__attribute__((unused)) unsigned long index)
{
    return rand_range(0, 1);
}

double fill_rand_1_1(__attribute__((unused)) unsigned long index)
{
    return rand_range(-1, 1);
}

double fill_inc(unsigned long index)
{
    return (double)index;
}

#endif // CSYNTH_BUFFER_H

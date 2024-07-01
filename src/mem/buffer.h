//
// buffer.h - A (cyclic) sample buffer with dynamic resizing.
//
#ifndef CSYNTH_BUFFER_H
#define CSYNTH_BUFFER_H

#include <stdlib.h>
#include <string.h>

#include "../mem/alloc.h"
#include "../util/error.h"
#include "../util/rand.h"

typedef struct
{
    double *samples;
    size_t size;
    size_t capacity;
} Buffer;

csError buffer_init(Buffer *buffer, size_t size)
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

void buffer_fill(Buffer *buffer, double (*fill)(size_t))
{
    if (fill != NULL)
    {
        for (size_t i = 0; i < buffer->size; i++)
        {
            buffer->samples[i] = fill(i);
        }
    }
    else
    {
        memset(buffer->samples, 0, buffer->size * sizeof(double));
    }
}

static size_t buffer_resize_from_zero(Buffer *buffer, size_t size, double (*fill)(size_t))
{
    double *samples = (double *)malloc_(size * sizeof(double));
    if (samples == NULL)
    {
        error_catch(csErrorMemoryAlloc);
        // TODO(leo): handle error
        return 0;
    }
    buffer->samples = samples;
    buffer->capacity = size;
    buffer->size = size;
    buffer_fill(buffer, fill);
    return 0;
}

static size_t buffer_resize_to_zero(Buffer *buffer)
{
    free_(buffer->samples);
    buffer->samples = NULL;
    buffer->capacity = 0;
    buffer->size = 0;
    return 0;
}

static size_t buffer_resize_up(Buffer *buffer, size_t size, size_t index, double (*fill)(size_t))
{
    if (size > buffer->capacity)
    {
        size_t capacity = size * 2;
        double *samples = (double *)realloc_(buffer->samples, capacity * sizeof(double));
        if (samples == NULL)
        {
            error_catch(csErrorMemoryAlloc);
            return index;
        }
        buffer->capacity = capacity;
        buffer->samples = samples;
    }
    size_t diff = buffer->size - index;
    size_t too = size - diff;
    memmove(buffer->samples + too, buffer->samples + index, diff * sizeof(double));
    if (fill != NULL)
    {
        for (size_t i = index, end = size - diff; i < end; i++)
        {
            buffer->samples[i] = fill(i);
        }
    }
    else
    {
        size_t gap = size - buffer->size;
        memset(buffer->samples + index, 0, gap * sizeof(double));
    }
    buffer->size = size;
    return index;
}

static size_t buffer_resize_down(Buffer *buffer, size_t size, size_t index)
{
    if (index < size)
    {
        size_t diff = size - index;
        size_t from = buffer->size - diff;
        memmove(buffer->samples + index, buffer->samples + from, diff * sizeof(double));
    }
    else if (index > size)
    {
        size_t diff = index - size;
        memmove(buffer->samples, buffer->samples + size, diff * sizeof(double));
        index -= size;
    }
    else
    {
        index = 0;
    }
    buffer->size = size;
    return index;
}

size_t buffer_resize(Buffer *buffer, size_t size, size_t index, double (*fill)(size_t))
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

double fill_rand_0_1(__attribute__((unused)) size_t index)
{
    return rand_range(0, 1);
}

double fill_rand_1_1(__attribute__((unused)) size_t index)
{
    return rand_range(-1, 1);
}

double fill_inc(size_t index)
{
    return (double)index;
}

#endif // CSYNTH_BUFFER_H

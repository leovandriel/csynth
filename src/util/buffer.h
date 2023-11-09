//
// buffer.h - A (cyclic) sample buffer with dynamic resizing.
//
#ifndef CSYNTH_BUFFER_H
#define CSYNTH_BUFFER_H

#include <string.h>
#include <stdlib.h>

#include "./test.h"
#include "./rand.h"

typedef struct
{
    double *samples;
    unsigned long size;
    unsigned long max;
} Buffer;

void buffer_init(Buffer *buffer, unsigned long size)
{
    buffer->samples = (double *)calloc(size, sizeof(double));
    buffer->max = size;
    buffer->size = size;
}

static unsigned long buffer_resize_from_zero(Buffer *buffer, unsigned long size, double (*fill)(unsigned long))
{
    buffer->samples = (double *)calloc(size, sizeof(double));
    if (fill != NULL)
    {
        for (unsigned long i = 0; i < size; i++)
        {
            buffer->samples[i] = fill(i);
        }
    }
    buffer->max = size;
    buffer->size = size;
    return 0;
}

static unsigned long buffer_resize_to_zero(Buffer *buffer)
{
    free(buffer->samples);
    buffer->samples = NULL;
    buffer->max = 0;
    buffer->size = 0;
    return 0;
}

static unsigned long buffer_resize_up(Buffer *buffer, unsigned long size, unsigned long index, double (*fill)(unsigned long))
{
    if (size > buffer->max)
    {
        unsigned long max = size * 2;
        buffer->samples = (double *)realloc(buffer->samples, max * sizeof(double));
        buffer->max = max;
    }
    unsigned long diff = size - buffer->size;
    unsigned long to = index + diff;
    memmove(buffer->samples + to, buffer->samples + index, diff * sizeof(double));
    if (fill != NULL)
    {
        for (unsigned long i = index, e = index + diff; i < e; i++)
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
    free(buffer->samples);
}

double fill_rand_0_1(__attribute__((unused)) unsigned long index)
{
    return rand_double();
}

double fill_rand_1_1(__attribute__((unused)) unsigned long index)
{
    return 2.0 * rand_double() - 1.0;
}

double fill_inc(unsigned long index)
{
    return index;
}

static void test_same()
{
    Buffer buffer;
    buffer_init(&buffer, 2);
    buffer.samples[0] = 1;
    buffer.samples[1] = 2;
    assert(buffer_resize(&buffer, 2, 3, fill_inc) == 3);
    assert(buffer.samples != NULL);
    assert(buffer.size == 2);
    assert(buffer.max == 2);
    assert(buffer.samples[0] == 1);
    assert(buffer.samples[1] == 2);
}

static void test_from_zero()
{
    Buffer buffer;
    buffer_init(&buffer, 0);
    assert(buffer_resize(&buffer, 2, 3, fill_inc) == 0);
    assert(buffer.samples != NULL);
    assert(buffer.size == 2);
    assert(buffer.max == 2);
    assert(buffer.samples[0] == 0);
    assert(buffer.samples[1] == 1);
    buffer_free(&buffer);
}

static void test_to_zero()
{
    Buffer buffer;
    buffer_init(&buffer, 2);
    buffer.samples[0] = 1;
    buffer.samples[1] = 2;
    assert(buffer_resize(&buffer, 0, 3, fill_inc) == 0);
    assert(buffer.samples == NULL);
    assert(buffer.size == 0);
    assert(buffer.max == 0);
    buffer_free(&buffer);
}

static void test_up()
{
    for (unsigned long i = 0; i < 2; i++)
    {
        Buffer buffer;
        buffer_init(&buffer, 2);
        buffer.samples[0] = 1;
        buffer.samples[1] = 2;
        assert(buffer_resize(&buffer, 4, i, fill_inc) == i);
        assert(buffer.samples != NULL);
        assert(buffer.size == 4);
        assert(buffer.max == 8);
        double s[] = {0, 1, 1, 1, 1, 2, 2, 2};
        assert(buffer.samples[0] == s[i]);
        assert(buffer.samples[1] == s[i + 2]);
        assert(buffer.samples[2] == s[i + 4]);
        assert(buffer.samples[3] == s[i + 6]);
        buffer_free(&buffer);
    }
}

static void test_down()
{
    for (unsigned long i = 0; i < 4; i++)
    {
        Buffer buffer;
        buffer_init(&buffer, 4);
        buffer.samples[0] = 1;
        buffer.samples[1] = 2;
        buffer.samples[2] = 3;
        buffer.samples[3] = 4;
        assert(buffer_resize(&buffer, 2, i, fill_inc) == i % 2);
        assert(buffer.samples != NULL);
        assert(buffer.size == 2);
        assert(buffer.max == 4);
        double s[] = {3, 1, 1, 3, 4, 4, 2, 2};
        assert(buffer.samples[0] == s[i]);
        assert(buffer.samples[1] == s[i + 4]);
        buffer_free(&buffer);
    }
}

void test_buffer()
{
    test_same();
    test_from_zero();
    test_to_zero();
    test_up();
    test_down();
}

#endif // CSYNTH_BUFFER_H

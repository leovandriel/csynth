#include "../../src/mem/buffer.h"
#include "../util/test.h"

static void test_same()
{
    Buffer buffer;
    buffer_init(&buffer, 2);
    buffer.samples[0] = 1;
    buffer.samples[1] = 2;
    assert(buffer_resize(&buffer, 2, 3, fill_inc) == 3);
    assert(buffer.samples != NULL);
    assert(buffer.size == 2);
    assert(buffer.capacity == 2);
    assert(buffer.samples[0] == 1);
    assert(buffer.samples[1] == 2);
    buffer_free(&buffer);
}

static void test_from_zero()
{
    Buffer buffer;
    buffer_init(&buffer, 0);
    assert(buffer_resize(&buffer, 2, 3, fill_inc) == 0);
    assert(buffer.samples != NULL);
    assert(buffer.size == 2);
    assert(buffer.capacity == 2);
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
    assert(buffer.capacity == 0);
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
        assert(buffer.capacity == 8);
        double samples[] = {0, 1, 1, 1, 1, 2, 2, 2};
        assert(buffer.samples[0] == samples[i]);
        assert(buffer.samples[1] == samples[i + 2]);
        assert(buffer.samples[2] == samples[i + 4]);
        assert(buffer.samples[3] == samples[i + 6]);
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
        assert(buffer.capacity == 4);
        double samples[] = {3, 1, 1, 3, 4, 4, 2, 2};
        assert(buffer.samples[0] == samples[i]);
        assert(buffer.samples[1] == samples[i + 4]);
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

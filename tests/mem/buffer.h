#include "../../src/mem/buffer.h"
#include "../util/test.h"

static void test_same()
{
    Buffer buffer;
    assert(buffer_init(&buffer, 2) == csErrorNone);
    buffer.samples[0] = 101;
    buffer.samples[1] = 102;
    assert(buffer_resize(&buffer, 2, 3, fill_inc) == 3);
    assert(buffer.samples != NULL);
    assert(buffer.size == 2);
    assert(buffer.capacity == 2);
    assert(buffer.samples[0] == 101);
    assert(buffer.samples[1] == 102);
    buffer_free(&buffer);
}

static void test_from_zero()
{
    Buffer buffer;
    assert(buffer_init(&buffer, 0) == csErrorNone);
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
    assert(buffer_init(&buffer, 2) == csErrorNone);
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
    for (size_t i = 0; i < 2; i++)
    {
        Buffer buffer;
        assert(buffer_init(&buffer, 2) == csErrorNone);
        buffer.samples[0] = 101;
        buffer.samples[1] = 102;
        assert(buffer_resize(&buffer, 4, i, fill_inc) == i);
        assert(buffer.samples != NULL);
        assert(buffer.size == 4);
        assert(buffer.capacity == 8);
        double samples[] = {0, 101, 1, 1, 101, 2, 102, 102};
        assert(buffer.samples[0] == samples[i]);
        assert(buffer.samples[1] == samples[i + 2]);
        assert(buffer.samples[2] == samples[i + 4]);
        assert(buffer.samples[3] == samples[i + 6]);
        buffer_free(&buffer);
    }
}

static void test_down()
{
    for (size_t i = 0; i < 4; i++)
    {
        Buffer buffer;
        assert(buffer_init(&buffer, 4) == csErrorNone);
        buffer.samples[0] = 101;
        buffer.samples[1] = 102;
        buffer.samples[2] = 103;
        buffer.samples[3] = 104;
        assert(buffer_resize(&buffer, 2, i, fill_inc) == i % 2);
        assert(buffer.samples != NULL);
        assert(buffer.size == 2);
        assert(buffer.capacity == 4);
        double samples[] = {103, 101, 101, 103, 104, 104, 102, 102};
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

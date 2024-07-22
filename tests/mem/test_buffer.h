#include "../../src/mem/buffer.h"
#include "../../src/mem/fill.h"
#include "../util/test.h"

static void test_same(void)
{
    Buffer buffer = {.filler = fill_inc};
    assert(buffer_resize(&buffer, 2, 0) == 0);
    buffer.samples[0] = 101;
    buffer.samples[1] = 102;
    assert(buffer_resize(&buffer, 2, 3) == 3);
    assert(buffer.samples != NULL);
    assert(buffer.size == 2);
    assert(buffer.capacity == 2);
    assert(buffer.samples[0] == 101);
    assert(buffer.samples[1] == 102);
    buffer_free(&buffer);
}

static void test_from_zero(void)
{
    Buffer buffer = {.filler = fill_inc};
    assert(buffer_resize(&buffer, 2, 3) == 0);
    assert(buffer.samples != NULL);
    assert(buffer.size == 2);
    assert(buffer.capacity == 2);
    assert(buffer.samples[0] == 0);
    assert(buffer.samples[1] == 1);
    buffer_free(&buffer);
}

static void test_to_zero(void)
{
    Buffer buffer = {.filler = fill_inc};
    assert(buffer_resize(&buffer, 2, 0) == 0);
    buffer.samples[0] = 1;
    buffer.samples[1] = 2;
    assert(buffer_resize(&buffer, 0, 3) == 0);
    assert(buffer.samples == NULL);
    assert(buffer.size == 0);
    assert(buffer.capacity == 0);
    buffer_free(&buffer);
}

static void test_up(void)
{
    for (size_t i = 0; i < 2; i++)
    {
        Buffer buffer = {.filler = fill_inc};
        assert(buffer_resize(&buffer, 2, 0) == 0);
        buffer.samples[0] = 101;
        buffer.samples[1] = 102;
        assert(buffer_resize(&buffer, 4, i) == i);
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

static void test_down(void)
{
    for (size_t i = 0; i < 4; i++)
    {
        Buffer buffer = {.filler = fill_inc};
        assert(buffer_resize(&buffer, 4, 0) == 0);
        buffer.samples[0] = 101;
        buffer.samples[1] = 102;
        buffer.samples[2] = 103;
        buffer.samples[3] = 104;
        assert(buffer_resize(&buffer, 2, i) == i % 2);
        assert(buffer.samples != NULL);
        assert(buffer.size == 2);
        assert(buffer.capacity == 4);
        double samples[] = {103, 101, 101, 103, 104, 104, 102, 102};
        assert(buffer.samples[0] == samples[i]);
        assert(buffer.samples[1] == samples[i + 4]);
        buffer_free(&buffer);
    }
}

void test_buffer(void)
{
    test_same();
    test_from_zero();
    test_to_zero();
    test_up();
    test_down();
}

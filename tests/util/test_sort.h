#include "../../src/util/sort.h"
#include "./test.h"
#include <string.h>

static int compare_int_ascending(const void *a, const void *b, const void *context)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    (void)context;
    if (ia < ib)
        return -1;
    if (ia > ib)
        return 1;
    return 0;
}

static int compare_int_descending(const void *a, const void *b, const void *context)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    (void)context;
    if (ia > ib)
        return -1;
    if (ia < ib)
        return 1;
    return 0;
}

static int compare_int_with_context(const void *a, const void *b, const void *context)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    int multiplier = *(const int *)context;
    int result = (ia - ib) * multiplier;
    if (result < 0)
        return -1;
    if (result > 0)
        return 1;
    return 0;
}

void test_sort_int_ascending(void)
{
    int values[] = {5, 2, 8, 1, 9, 3};
    int expected[] = {1, 2, 3, 5, 8, 9};
    size_t count = sizeof(values) / sizeof(values[0]);

    sort(values, count, sizeof(int), compare_int_ascending, NULL);

    for (size_t i = 0; i < count; i++)
    {
        assert_long_equal(values[i], expected[i]);
    }
}

void test_sort_int_descending(void)
{
    int values[] = {5, 2, 8, 1, 9, 3};
    int expected[] = {9, 8, 5, 3, 2, 1};
    size_t count = sizeof(values) / sizeof(values[0]);

    sort(values, count, sizeof(int), compare_int_descending, NULL);

    for (size_t i = 0; i < count; i++)
    {
        assert_long_equal(values[i], expected[i]);
    }
}

void test_sort_int_already_sorted(void)
{
    int values[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(values) / sizeof(values[0]);

    sort(values, count, sizeof(int), compare_int_ascending, NULL);

    for (size_t i = 0; i < count; i++)
    {
        assert_long_equal(values[i], expected[i]);
    }
}

void test_sort_int_reverse_sorted(void)
{
    int values[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(values) / sizeof(values[0]);

    sort(values, count, sizeof(int), compare_int_ascending, NULL);

    for (size_t i = 0; i < count; i++)
    {
        assert_long_equal(values[i], expected[i]);
    }
}

void test_sort_int_duplicates(void)
{
    int values[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int expected[] = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    size_t count = sizeof(values) / sizeof(values[0]);

    sort(values, count, sizeof(int), compare_int_ascending, NULL);

    for (size_t i = 0; i < count; i++)
    {
        assert_long_equal(values[i], expected[i]);
    }
}

void test_sort_int_single_element(void)
{
    int values[] = {42};
    int expected[] = {42};
    size_t count = sizeof(values) / sizeof(values[0]);

    sort(values, count, sizeof(int), compare_int_ascending, NULL);

    assert_long_equal(values[0], expected[0]);
}

void test_sort_int_empty(void)
{
    int values[] = {};
    size_t count = 0;

    sort(values, count, sizeof(int), compare_int_ascending, NULL);

    assert_long_equal(count, 0);
}

void test_sort_int_with_context(void)
{
    int values[] = {5, 2, 8, 1, 9, 3};
    int expected_asc[] = {1, 2, 3, 5, 8, 9};
    int expected_desc[] = {9, 8, 5, 3, 2, 1};
    size_t count = sizeof(values) / sizeof(values[0]);

    int multiplier_asc = 1;
    sort(values, count, sizeof(int), compare_int_with_context, &multiplier_asc);
    for (size_t i = 0; i < count; i++)
    {
        assert_long_equal(values[i], expected_asc[i]);
    }

    int multiplier_desc = -1;
    sort(values, count, sizeof(int), compare_int_with_context, &multiplier_desc);
    for (size_t i = 0; i < count; i++)
    {
        assert_long_equal(values[i], expected_desc[i]);
    }
}

void test_sort(void)
{
    test_sort_int_ascending();
    test_sort_int_descending();
    test_sort_int_already_sorted();
    test_sort_int_reverse_sorted();
    test_sort_int_duplicates();
    test_sort_int_single_element();
    test_sort_int_empty();
    test_sort_int_with_context();
}

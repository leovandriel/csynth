#ifndef FILE_TRACE
#define FILE_TRACE
#endif

#include "../../src/func/gen/const.h"
#include "../../src/io/file.h"
#include "../util/test.h"

void test_file(void)
{
    assert_long_equal(file_list_is_empty(), 1);
    assert_long_equal(file_count(), 0);
    FileStat stat = file_stat();
    assert_long_equal(stat.open_count, 0);
    assert_long_equal(stat.close_count, 0);
    FILE *file = fopen_("output/test.txt", "w");
    assert_long_equal(file_list_is_empty(), 0);
    assert_long_equal(file_count(), 1);
    stat = file_stat();
    assert_long_equal(stat.open_count, 1);
    assert_long_equal(stat.close_count, 0);
    int error = fclose_(file);
    assert_long_equal(error, 0);
    assert_long_equal(file_list_is_empty(), 1);
    assert_long_equal(file_count(), 0);
    stat = file_stat();
    assert_long_equal(stat.open_count, 0);
    assert_long_equal(stat.close_count, 1);
}

#ifndef ALLOC_TRACE
#define ALLOC_TRACE
#endif

#include "../../src/func/gen/const.h"
#include "../../src/mem/alloc.h"
#include "../util/test.h"

void test_alloc(void)
{
    assert_long_equal(alloc_list_is_empty(), 1);
    const_create(0.0);
    assert_long_equal(alloc_size(), 104);
    AllocStat stat = alloc_stat();
    assert_long_equal(stat.alloc_count, 2);
    assert_long_equal(stat.alloc_size, 104);
    assert_long_equal(stat.free_count, 0);
    assert_long_equal(stat.free_size, 0);
    func_free();
    assert_long_equal(alloc_size(), 0);
    stat = alloc_stat();
    assert_long_equal(stat.alloc_count, 0);
    assert_long_equal(stat.alloc_size, 0);
    assert_long_equal(stat.free_count, 2);
    assert_long_equal(stat.free_size, 104);
    assert_long_equal(alloc_list_is_empty(), 1);
}

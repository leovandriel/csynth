#include "../../src/func/gen/const.h"
#include "../../src/util/func_tools.h"
#include "../util/test.h"

void test_func_tools(void)
{
    FuncStat stat = func_stats(const_create(1));
    assert_long_equal(stat.count, 1);
    assert_long_equal(stat.items[0].count, 1);
    assert_string_equal(stat.items[0].name, "const_eval");
    func_free();
}

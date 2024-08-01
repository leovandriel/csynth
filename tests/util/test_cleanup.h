#include "../../src/func/gen/const.h"
#include "../../src/util/cleanup.h"
#include "../util/test.h"

void test_cleanup(void)
{
    const_create(0);
    cleanup_all();
}

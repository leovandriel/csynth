#include "../../../src/func/op/max.h"
#include "../../util/test.h"

void test_max()
{
    Gen *gen1 = gen_create(max(const_(1), const_(2)), .1);
    Gen *gen2 = gen_create(max(const_(2), const_(1)), .1);
    Gen *gen3 = gen_create(max(const_(4), const_(2), const_(3)), .1);
    Gen *gen4 = gen_create(max(const_(1)), .1);
    assert_gen_equal(gen1, 2.0);
    assert_gen_equal(gen2, 2.0);
    assert_gen_equal(gen3, 4.0);
    assert_gen_equal(gen4, 1.0);
    gen_free(gen1);
    gen_free(gen2);
    gen_free(gen3);
    gen_free(gen4);
    func_free();
}

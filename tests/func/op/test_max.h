#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/max.h"
#include "../../util/test.h"

void test_max()
{
    Gen *gen1 = gen_create(max_create(ARGS(const_(1), const_(2))));
    Gen *gen2 = gen_create(max_create(ARGS(const_(2), const_(1))));
    Gen *gen3 = gen_create(max_create(ARGS(const_(4), const_(2), const_(3))));
    Gen *gen4 = gen_create(max_create(ARGS(const_(1))));
    assert_double_equal(gen_eval(gen1, NULL), 2.0);
    assert_double_equal(gen_eval(gen2, NULL), 2.0);
    assert_double_equal(gen_eval(gen3, NULL), 4.0);
    assert_double_equal(gen_eval(gen4, NULL), 1.0);
    gen_free(gen1);
    gen_free(gen2);
    gen_free(gen3);
    gen_free(gen4);
    func_free();
}

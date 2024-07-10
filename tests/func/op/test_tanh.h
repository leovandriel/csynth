#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/tanh.h"
#include "../../util/test.h"

void test_tanh()
{
    Gen *gen1 = gen_create(tanh_create(const_(0)));
    Gen *gen2 = gen_create(tanh_create(const_(1)));
    Gen *gen3 = gen_create(tanh_create(const_(2)));
    assert_double_equal(gen_eval(gen1, NULL), 0.0);
    assert_double_equal(gen_eval(gen2, NULL), 0.7615941559557649);
    assert_double_equal(gen_eval(gen3, NULL), 0.9640275800758169);
    gen_free(gen1);
    gen_free(gen2);
    gen_free(gen3);
    func_free();
}

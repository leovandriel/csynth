#include "../../../src/func/filter/sample.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/rand.h"
#include "../../util/test.h"

void test_sample(void)
{
    Gen *gen = gen_create(sample_create(rand_create()));
    assert_double_equal(gen_eval(gen, NULL), 0.0625038757098120);
    assert_double_equal(gen_eval(gen, NULL), 0.0625038757098120);
    assert_double_equal(gen_eval(gen, NULL), 0.0625038757098120);
    assert_double_equal(gen_eval(gen, NULL), 0.0625038757098120);
    gen_free(gen);
    func_free();
}

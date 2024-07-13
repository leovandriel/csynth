#include "../../../src/func/effect/reverb.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/saw.h"
#include "../../util/test.h"

void test_reverb()
{
    Gen *gen = gen_create(reverb_create(const_(0.2), const_(0.5), saw_create(const_(0.1))));
    assert_double_equal(gen_eval(gen, NULL), 0.00);
    assert_double_equal(gen_eval(gen, NULL), 0.20);
    assert_double_equal(gen_eval(gen, NULL), 0.40);
    assert_double_equal(gen_eval(gen, NULL), 0.60);
    assert_double_equal(gen_eval(gen, NULL), 0.80);
    assert_double_equal(gen_eval(gen, NULL), 1.00);
    assert_double_equal(gen_eval(gen, NULL), -0.70);
    assert_double_equal(gen_eval(gen, NULL), -0.40);
    assert_double_equal(gen_eval(gen, NULL), -0.10);
    assert_double_equal(gen_eval(gen, NULL), 0.20);
    assert_double_equal(gen_eval(gen, NULL), 0.50);
    assert_double_equal(gen_eval(gen, NULL), -0.15);
    gen_free(gen);
    func_free();
}

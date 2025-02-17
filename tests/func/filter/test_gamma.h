#include "../../../src/func/filter/gamma.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/triangle.h"
#include "../../util/test.h"

void test_gamma(void)
{
    Gen *gen = gen_create(gamma_create(triangle_create(const_create(.1), const_create(0)), const_create(2), map_gamma));
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.6400000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.9600000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.9600000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.6399999999999997);
    assert_double_equal(gen_eval(gen, NULL), -0.0000000000000004);
    assert_double_equal(gen_eval(gen, NULL), -0.6400000000000003);
    assert_double_equal(gen_eval(gen, NULL), -0.9600000000000001);
    assert_double_equal(gen_eval(gen, NULL), -0.9600000000000000);
    assert_double_equal(gen_eval(gen, NULL), -0.6399999999999997);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000004);
    assert_double_equal(gen_eval(gen, NULL), 0.6400000000000003);
    gen_free(gen);
    func_free();
}

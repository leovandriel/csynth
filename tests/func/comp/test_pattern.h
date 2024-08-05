#include "../../../src/func/comp/pattern.h"
#include "../../../src/func/gen/impulse.h"
#include "../../util/test.h"

void test_pattern(void)
{
    Gen *gen = gen_create(pattern_create("....", const_create(.2), const_create(.01), impulse_create()));
    assert_double_equal(gen_eval(gen, NULL), 1.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 1.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 1.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    gen_free(gen);
    func_free();
}

#include "../../../src/func/filter/slope.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/square.h"
#include "../../util/test.h"

void test_slope()
{
    Gen *gen = gen_create(slope_create(const_(0.1), square_create(const_(0.2))));
    assert_double_equal(gen_eval(gen, NULL), 0.1);
    assert_double_equal(gen_eval(gen, NULL), 0.2);
    assert_double_equal(gen_eval(gen, NULL), 0.3);
    assert_double_equal(gen_eval(gen, NULL), 0.2);
    assert_double_equal(gen_eval(gen, NULL), 0.1);
    assert_double_equal(gen_eval(gen, NULL), 0.2);
    assert_double_equal(gen_eval(gen, NULL), 0.3);
    assert_double_equal(gen_eval(gen, NULL), 0.4);
    assert_double_equal(gen_eval(gen, NULL), 0.3);
    assert_double_equal(gen_eval(gen, NULL), 0.2);
    assert_double_equal(gen_eval(gen, NULL), 0.3);
    assert_double_equal(gen_eval(gen, NULL), 0.4);
    gen_free(gen);
    func_free();
}

#include "../../../src/func/filter/limit.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/square.h"
#include "../../util/test.h"

void test_limit()
{
    Gen *gen = gen_create(limit_create(const_(0.3), square_create(const_(0.1))));
    assert_double_equal(gen_eval(gen, NULL), 0.30);
    assert_double_equal(gen_eval(gen, NULL), 0.60);
    assert_double_equal(gen_eval(gen, NULL), 0.90);
    assert_double_equal(gen_eval(gen, NULL), 1.00);
    assert_double_equal(gen_eval(gen, NULL), 1.00);
    assert_double_equal(gen_eval(gen, NULL), 0.70);
    assert_double_equal(gen_eval(gen, NULL), 0.40);
    assert_double_equal(gen_eval(gen, NULL), 0.10);
    assert_double_equal(gen_eval(gen, NULL), -0.20);
    assert_double_equal(gen_eval(gen, NULL), -0.50);
    assert_double_equal(gen_eval(gen, NULL), -0.20);
    assert_double_equal(gen_eval(gen, NULL), 0.10);
    gen_free(gen);
    func_free();
}

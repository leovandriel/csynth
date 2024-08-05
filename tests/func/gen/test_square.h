#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/square.h"
#include "../../util/test.h"

void test_square_exact(void)
{
    Gen *gen = gen_create(square_create(const_create(0.1)));
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), -1.0);
    assert_double_equal(gen_eval(gen, NULL), -1.0);
    assert_double_equal(gen_eval(gen, NULL), -1.0);
    assert_double_equal(gen_eval(gen, NULL), -1.0);
    assert_double_equal(gen_eval(gen, NULL), -1.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    gen_free(gen);
}

void test_square_range(void)
{
    for (size_t i = 0; i < 100; i++)
    {
        Gen *gen = gen_create(square_create(const_create(0.1)));
        assert_double_range(gen_eval(gen, NULL), -1.0, 1.0);
        gen_free(gen);
    }
}

void test_square(void)
{
    test_square_exact();
    test_square_range();
    func_free();
}
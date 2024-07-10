#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/saw.h"
#include "../../util/test.h"

void test_saw_exact()
{
    Gen *gen = gen_create(saw_create(const_(0.1)));
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.2);
    assert_double_equal(gen_eval(gen, NULL), 0.4);
    assert_double_equal(gen_eval(gen, NULL), 0.6);
    assert_double_equal(gen_eval(gen, NULL), 0.8);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), -0.8);
    assert_double_equal(gen_eval(gen, NULL), -0.6);
    assert_double_equal(gen_eval(gen, NULL), -0.4);
    assert_double_equal(gen_eval(gen, NULL), -0.2);
    assert_double_equal(gen_eval(gen, NULL), -0.0);
    gen_free(gen);
}

void test_saw_range()
{
    for (size_t i = 0; i < 100; i++)
    {
        Gen *gen = gen_create(saw_create(const_(0.1)));
        assert_double_range(gen_eval(gen, NULL), -1.0, 1.0);
        gen_free(gen);
    }
}

void test_saw()
{
    test_saw_exact();
    test_saw_range();
    func_free();
}
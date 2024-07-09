#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/triangle.h"
#include "../../util/test.h"

void test_triangle_exact()
{
    Func *time = triangle_create(const_(0.1));
    Gen *gen = gen_create(time);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.4);
    assert_double_equal(gen_eval(gen, &eval), 0.8);
    assert_double_equal(gen_eval(gen, &eval), 0.8);
    assert_double_equal(gen_eval(gen, &eval), 0.4);
    assert_double_equal(gen_eval(gen, &eval), -0.0);
    assert_double_equal(gen_eval(gen, &eval), -0.4);
    assert_double_equal(gen_eval(gen, &eval), -0.8);
    assert_double_equal(gen_eval(gen, &eval), -0.8);
    assert_double_equal(gen_eval(gen, &eval), -0.4);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.4);
    gen_free(gen);
    func_free();
}

void test_triangle_range()
{
    for (size_t i = 0; i < 100; i++)
    {
        Gen *gen = gen_create(triangle_create(const_(0.1)));
        Eval eval = eval_create(0.1);
        assert_double_range(gen_eval(gen, &eval), -1.0, 1.0);
        gen_free(gen);
    }
    func_free();
}

void test_triangle()
{
    test_triangle_exact();
    test_triangle_range();
}
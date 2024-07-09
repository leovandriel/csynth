#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/square.h"
#include "../../util/test.h"

void test_square_exact()
{
    Func *time = square_create(const_(0.1));
    Gen *gen = gen_create(time);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), -1.0);
    assert_double_equal(gen_eval(gen, &eval), -1.0);
    assert_double_equal(gen_eval(gen, &eval), -1.0);
    assert_double_equal(gen_eval(gen, &eval), -1.0);
    assert_double_equal(gen_eval(gen, &eval), -1.0);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    gen_free(gen);
    func_free();
}

void test_square_range()
{
    for (size_t i = 0; i < 100; i++)
    {
        Gen *gen = gen_create(square_create(const_(0.1)));
        Eval eval = eval_create(0.1);
        assert_double_range(gen_eval(gen, &eval), -1.0, 1.0);
        gen_free(gen);
    }
    func_free();
}

void test_square()
{
    test_square_exact();
    test_square_range();
}
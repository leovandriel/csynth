#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/rand.h"
#include "../../util/test.h"

void test_rand_exact(void)
{
    Gen *gen = gen_create(rand_create());
    assert_double_equal(gen_eval(gen, NULL), 0.0625038757098120);
    assert_double_equal(gen_eval(gen, NULL), 0.6059343925285466);
    assert_double_equal(gen_eval(gen, NULL), 0.9583275921953511);
    assert_double_equal(gen_eval(gen, NULL), 0.5236224943222167);
    assert_double_equal(gen_eval(gen, NULL), 0.9636279947347471);
    assert_double_equal(gen_eval(gen, NULL), 0.6338806769160699);
    assert_double_equal(gen_eval(gen, NULL), 0.7741184088125456);
    assert_double_equal(gen_eval(gen, NULL), 0.4892274845865111);
    assert_double_equal(gen_eval(gen, NULL), 0.4517149853511886);
    assert_double_equal(gen_eval(gen, NULL), 0.1124688246148232);
    assert_double_equal(gen_eval(gen, NULL), 0.9362395387648647);
    assert_double_equal(gen_eval(gen, NULL), 0.3053379691174754);
    gen_free(gen);
}

void test_rand_range(void)
{
    for (size_t i = 0; i < 100; i++)
    {
        Gen *gen = gen_create(rand_create());
        assert_double_range(gen_eval(gen, NULL), -1.0, 1.0);
        gen_free(gen);
    }
}

void test_rand(void)
{
    test_rand_exact();
    test_rand_range();
    func_free();
}
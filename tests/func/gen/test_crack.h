#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/crack.h"
#include "../../util/test.h"

void test_crack_exact(void)
{
    rand_seed(0);
    Gen *gen = gen_create(crack_create(const_(0.5)));
    assert_double_equal(gen_eval(gen, NULL), 0.2118687850570933);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), -0.0965700292976227);
    assert_double_equal(gen_eval(gen, NULL), 0.8724790775297293);
    assert_double_equal(gen_eval(gen, NULL), 0.1319687240920917);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.3212592466848991);
    gen_free(gen);
}

void test_crack_range(void)
{
    for (size_t i = 0; i < 100; i++)
    {
        Gen *gen = gen_create(crack_create(const_(0.1)));
        assert_double_range(gen_eval(gen, NULL), -1.0, 1.0);
        gen_free(gen);
    }
}

void test_crack(void)
{
    test_crack_exact();
    test_crack_range();
    func_free();
}
#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/uniform.h"
#include "../../util/test.h"

void test_uniform_exact(void)
{
    rand_seed(0);
    Gen *gen = gen_create(uniform_create());
    assert_double_equal(gen_eval(gen, NULL), -0.8749922485803759);
    assert_double_equal(gen_eval(gen, NULL), 0.2118687850570933);
    assert_double_equal(gen_eval(gen, NULL), 0.9166551843907023);
    assert_double_equal(gen_eval(gen, NULL), 0.0472449886444335);
    assert_double_equal(gen_eval(gen, NULL), 0.9272559894694943);
    assert_double_equal(gen_eval(gen, NULL), 0.2677613538321397);
    assert_double_equal(gen_eval(gen, NULL), 0.5482368176250911);
    assert_double_equal(gen_eval(gen, NULL), -0.0215450308269778);
    assert_double_equal(gen_eval(gen, NULL), -0.0965700292976227);
    assert_double_equal(gen_eval(gen, NULL), -0.7750623507703536);
    assert_double_equal(gen_eval(gen, NULL), 0.8724790775297293);
    assert_double_equal(gen_eval(gen, NULL), -0.3893240617650492);
    gen_free(gen);
}

void test_uniform_range(void)
{
    for (size_t i = 0; i < 100; i++)
    {
        Gen *gen = gen_create(uniform_create());
        assert_double_range(gen_eval(gen, NULL), -1.0, 1.0);
        gen_free(gen);
    }
}

void test_uniform(void)
{
    test_uniform_exact();
    test_uniform_range();
    func_free();
}
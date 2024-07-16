#include "../../../src/func/gen/pink.h"
#include "../../util/test.h"

void test_pink_exact(void)
{
    rand_seed(0);
    Gen *gen = gen_create(pink_create());
    assert_double_equal(gen_eval(gen, NULL), -0.1585402095170537);
    assert_double_equal(gen_eval(gen, NULL), -0.0549794888313561);
    assert_double_equal(gen_eval(gen, NULL), 0.1253204129478243);
    assert_double_equal(gen_eval(gen, NULL), 0.0671443718725813);
    assert_double_equal(gen_eval(gen, NULL), 0.2062575344240014);
    assert_double_equal(gen_eval(gen, NULL), 0.1767452112858754);
    assert_double_equal(gen_eval(gen, NULL), 0.2186729771903827);
    assert_double_equal(gen_eval(gen, NULL), 0.1521125834873314);
    assert_double_equal(gen_eval(gen, NULL), 0.1035000375597110);
    assert_double_equal(gen_eval(gen, NULL), -0.0427394077791834);
    assert_double_equal(gen_eval(gen, NULL), 0.1643236159074953);
    assert_double_equal(gen_eval(gen, NULL), 0.0494732029892094);
    gen_free(gen);
}

void test_pink_range(void)
{
    for (size_t i = 0; i < 100; i++)
    {
        Gen *gen = gen_create(pink_create());
        assert_double_range(gen_eval(gen, NULL), -1.0, 1.0);
        gen_free(gen);
    }
}

void test_pink(void)
{
    test_pink_exact();
    test_pink_range();
    func_free();
}
#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/gauss.h"
#include "../../util/test.h"

void test_gauss_exact(void)
{
    rand_seed(0);
    Gen *gen = gen_create(gauss_create());
    assert_double_equal(gen_eval(gen, NULL), -1.8521466561199877);
    assert_double_equal(gen_eval(gen, NULL), -0.2885645772717212);
    assert_double_equal(gen_eval(gen, NULL), -0.1814492681149756);
    assert_double_equal(gen_eval(gen, NULL), -0.7139457372660785);
    assert_double_equal(gen_eval(gen, NULL), 0.9588172018638266);
    assert_double_equal(gen_eval(gen, NULL), -0.1236863080479640);
    assert_double_equal(gen_eval(gen, NULL), -1.0379135510746773);
    assert_double_equal(gen_eval(gen, NULL), 0.5088091939943790);
    assert_double_equal(gen_eval(gen, NULL), 0.8499913834196360);
    assert_double_equal(gen_eval(gen, NULL), 1.2053862671832665);
    assert_double_equal(gen_eval(gen, NULL), 0.9852832177455417);
    assert_double_equal(gen_eval(gen, NULL), 0.1122575687337664);
    gen_free(gen);
}

void test_gauss_range(void)
{
    for (size_t i = 0; i < 100; i++)
    {
        Gen *gen = gen_create(gauss_create());
        assert_double_range(gen_eval(gen, NULL), -4.0, 4.0);
        gen_free(gen);
    }
}

void test_gauss(void)
{
    test_gauss_exact();
    test_gauss_range();
    func_free();
}
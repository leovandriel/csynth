#include "../../../src/func/comp/comps.h"
#include "../../../src/func/comp/seq.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/impulse.h"
#include "../../util/test.h"

void test_seq_abs(void)
{
    Gen *gen = gen_create(seq_abs_create(ARGS(const_create(0.1), const_create(0.0), const_create(1), const_create(0.2), const_create(-1), const_create(0.5), const_create(0))));
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), -1.0);
    assert_double_equal(gen_eval(gen, NULL), -1.0);
    assert_double_equal(gen_eval(gen, NULL), -1.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    gen_free(gen);
}

void test_seq_rel(void)
{
    Gen *gen = gen_create(seq_rel_create(ARGS(const_create(0.1), const_create(1), const_create(0.2), const_create(-1), const_create(0.3))));
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), -1.0);
    assert_double_equal(gen_eval(gen, NULL), -1.0);
    assert_double_equal(gen_eval(gen, NULL), -1.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    gen_free(gen);
}

void test_seq_seq(void)
{
    Gen *gen = gen_create(seq_seq_create(ARGS(impulse_create(), impulse_create())));
    assert_double_equal(gen_eval(gen, NULL), 1.0000000000000000);
    for (size_t i = 0; i < 10; i++)
    {
        assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    }
    assert_double_equal(gen_eval(gen, NULL), 1.0000000000000000);
    for (size_t i = 0; i < 10; i++)
    {
        assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    }
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    gen_free(gen);
}

void test_seq_fix(void)
{
    Gen *gen = gen_create(seq_fix_create(ARGS(const_create(0.5), const_create(1), const_create(-1))));
    assert_double_equal(gen_eval(gen, NULL), 1.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 1.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), -1.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), -1.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    gen_free(gen);
}

void test_seq(void)
{
    test_seq_abs();
    test_seq_rel();
    test_seq_seq();
    test_seq_fix();
    func_free();
}

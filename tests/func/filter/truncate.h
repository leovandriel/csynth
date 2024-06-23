#include "../../../src/func/filter/envelopes.h"
#include "../../../src/func/filter/truncate.h"
#include "../../util/test.h"

void test_truncate_miss()
{
    Func *input = add(rect_env_(0, .1), rect_env_(.5, .6));
    Func *trunc = truncate(input, const_(.00001));
    Gen *gen = gen_create(trunc, 0.1);
    assert_gen_equal(gen, 1.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 1.0);
    assert_gen_equal(gen, 0.0);
    gen_free(gen);
    func_free();
}

void test_truncate_hit()
{
    Func *input = add(rect_env_(0, .1), rect_env_(.8, .9));
    Func *trunc = truncate(input, const_(.00001));
    Gen *gen = gen_create(trunc, 0.1);
    assert_gen_equal(gen, 1.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.0);
    gen_free(gen);
    func_free();
}

void test_truncate()
{
    test_truncate_miss();
    test_truncate_hit();
}

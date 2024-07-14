#include "../../../src/func/comp/comps.h"
#include "../../../src/func/comp/seq.h"
#include "../../../src/func/gen/const.h"
#include "../../util/test.h"

void test_seq_abs()
{
}

void test_seq_rel()
{
    Gen *gen = gen_create(seq_rel_create(ARGS(const_(0.1), const_(1), const_(0.2), const_(-1), const_(0.3))));
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

void test_seq_seq()
{
}

void test_seq_fix()
{
}

void test_seq()
{
    test_seq_abs();
    test_seq_rel();
    test_seq_seq();
    test_seq_fix();
    func_free();
}

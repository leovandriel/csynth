#include "../../../src/func/comp/seq.h"
#include "../../../src/func/gen/const.h"
#include "../../util/test.h"

void test_seq()
{
    Func *t = seq_rel(const_(1), const_(0.2), const_(-1), const_(0.3));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, -1.0);
    assert_gen_equal(g, -1.0);
    assert_gen_equal(g, -1.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
}

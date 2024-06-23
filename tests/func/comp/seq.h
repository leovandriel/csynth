#include "../../../src/func/comp/seq.h"
#include "../../../src/func/gen/const.h"
#include "../../util/test.h"

void test_seq()
{
    Func *time = seq_rel(const_(1), const_(0.2), const_(-1), const_(0.3));
    Gen *gen = gen_create(time);
    Eval eval = {.audio_step = 0.1};
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), -1.0);
    assert_double_equal(gen_eval(gen, eval), -1.0);
    assert_double_equal(gen_eval(gen, eval), -1.0);
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 0.0);
    gen_free(gen);
    func_free();
}

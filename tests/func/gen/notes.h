#include "../../../src/func/gen/notes.h"
#include "../../util/test.h"

void test_notes()
{
    Gen *gen = gen_create(G9);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, eval), G9_);
    gen_free(gen);
    func_free();
}

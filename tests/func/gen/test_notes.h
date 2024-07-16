#include "../../../src/func/gen/notes.h"
#include "../../util/test.h"

void test_notes(void)
{
    Gen *gen = gen_create(G9);
    assert_double_equal(gen_eval(gen, NULL), G9_);
    gen_free(gen);
    func_free();
}

#include "../../../src/func/gen/notes.h"
#include "../../util/test.h"

void test_notes()
{
    Gen *gen = gen_create(G9, .1);
    assert_gen_equal(gen, G9_);
    gen_free(gen);
    func_free();
}

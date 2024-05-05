#include "../../../src/func/gen/notes.h"
#include "../../util/test.h"

void test_notes()
{
    assert_gen_equal(gen_create(G9, .1), G9_);
}

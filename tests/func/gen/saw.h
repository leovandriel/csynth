#include "../../../src/func/gen/saw.h"
#include "../../util/test.h"

void test_saw()
{
    Func *time = saw(const_(1));
    Gen *gen = gen_create(time, 0.1);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.2);
    assert_gen_equal(gen, 0.4);
    assert_gen_equal(gen, 0.6);
    assert_gen_equal(gen, 0.8);
    assert_gen_equal(gen, 1.0);
    assert_gen_equal(gen, -0.8);
    assert_gen_equal(gen, -0.6);
    assert_gen_equal(gen, -0.4);
    assert_gen_equal(gen, -0.2);
    assert_gen_equal(gen, -0.0);
}

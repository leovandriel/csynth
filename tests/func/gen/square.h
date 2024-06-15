#include "../../../src/func/gen/square.h"
#include "../../util/test.h"

void test_square()
{
    Func *time = square(const_(1));
    Gen *gen = gen_create(time, 0.1);
    assert_gen_equal(gen, 1.0);
    assert_gen_equal(gen, 1.0);
    assert_gen_equal(gen, 1.0);
    assert_gen_equal(gen, 1.0);
    assert_gen_equal(gen, 1.0);
    assert_gen_equal(gen, -1.0);
    assert_gen_equal(gen, -1.0);
    assert_gen_equal(gen, -1.0);
    assert_gen_equal(gen, -1.0);
    assert_gen_equal(gen, -1.0);
    assert_gen_equal(gen, 1.0);
    assert_gen_equal(gen, 1.0);
    gen_free(gen);
    func_free();
}

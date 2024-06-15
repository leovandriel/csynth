#include "../../../src/func/gen/triangle.h"
#include "../../util/test.h"

void test_triangle()
{
    Func *time = triangle(const_(1));
    Gen *gen = gen_create(time, 0.1);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.4);
    assert_gen_equal(gen, 0.8);
    assert_gen_equal(gen, 0.8);
    assert_gen_equal(gen, 0.4);
    assert_gen_equal(gen, -0.0);
    assert_gen_equal(gen, -0.4);
    assert_gen_equal(gen, -0.8);
    assert_gen_equal(gen, -0.8);
    assert_gen_equal(gen, -0.4);
    assert_gen_equal(gen, 0.0);
    assert_gen_equal(gen, 0.4);
    gen_free(gen);
    func_free();
}

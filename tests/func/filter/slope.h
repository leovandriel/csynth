#include "../../../src/func/filter/slope.h"
#include "../../../src/func/gen/square.h"
#include "../../util/test.h"

void test_slope()
{
    Func *func = slope(square_(2), const_(1));
    Gen *gen = gen_create(func, 0.1);
    assert_gen_equal(gen, 0.1);
    assert_gen_equal(gen, 0.2);
    assert_gen_equal(gen, 0.3);
    assert_gen_equal(gen, 0.2);
    assert_gen_equal(gen, 0.1);
    assert_gen_equal(gen, 0.2);
    assert_gen_equal(gen, 0.3);
    assert_gen_equal(gen, 0.4);
    assert_gen_equal(gen, 0.3);
    assert_gen_equal(gen, 0.2);
    assert_gen_equal(gen, 0.3);
    assert_gen_equal(gen, 0.4);
    gen_free(gen);
    func_free();
}

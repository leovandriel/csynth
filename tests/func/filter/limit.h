#include "../../../src/func/filter/limit.h"
#include "../../../src/func/gen/square.h"
#include "../../util/test.h"

void test_limit()
{
    Func *time = limit(square(const_(1)), const_(3));
    Gen *gen = gen_create(time, 0.1);
    assert_gen_equal(gen, 0.30);
    assert_gen_equal(gen, 0.60);
    assert_gen_equal(gen, 0.90);
    assert_gen_equal(gen, 1.00);
    assert_gen_equal(gen, 1.00);
    assert_gen_equal(gen, 0.70);
    assert_gen_equal(gen, 0.40);
    assert_gen_equal(gen, 0.10);
    assert_gen_equal(gen, -0.20);
    assert_gen_equal(gen, -0.50);
    assert_gen_equal(gen, -0.20);
    assert_gen_equal(gen, 0.10);
    gen_free(gen);
    func_free();
}

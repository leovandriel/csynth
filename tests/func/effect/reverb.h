#include "../../../src/func/effect/reverb.h"
#include "../../../src/func/gen/saw.h"
#include "../../util/test.h"

void test_reverb()
{
    Func *time = reverb(saw_(1), const_(.5), const_(.5));
    Gen *gen = gen_create(time, 0.1);
    assert_gen_equal(gen, 0.00);
    assert_gen_equal(gen, 0.20);
    assert_gen_equal(gen, 0.40);
    assert_gen_equal(gen, 0.60);
    assert_gen_equal(gen, 0.80);
    assert_gen_equal(gen, 1.00);
    assert_gen_equal(gen, -0.70);
    assert_gen_equal(gen, -0.40);
    assert_gen_equal(gen, -0.10);
    assert_gen_equal(gen, 0.20);
    assert_gen_equal(gen, 0.50);
    assert_gen_equal(gen, -0.15);
    gen_free(gen);
    func_free();
}

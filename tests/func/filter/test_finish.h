#include "../../../src/func/effect/delay.h"
#include "../../../src/func/filter/finish.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/impulse.h"
#include "../../../src/func/op/add.h"
#include "../../util/test.h"

void test_finish_miss(void)
{
    Func *input = add_create(ARGS_FUNC(impulse_create(), delay_create(const_create(0.2), impulse_create())));
    Func *trunc = finish_create(const_create(1.25), input);
    Gen *gen = gen_create(trunc);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    gen_free(gen);
}

void test_finish_hit(void)
{
    Func *input = add_create(ARGS_FUNC(impulse_create(), delay_create(const_create(0.1), impulse_create())));
    Func *trunc = finish_create(const_create(1.25), input);
    Gen *gen = gen_create(trunc);
    assert_double_equal(gen_eval(gen, NULL), 1.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    gen_free(gen);
}

void test_finish(void)
{
    test_finish_miss();
    test_finish_hit();
    func_free();
}

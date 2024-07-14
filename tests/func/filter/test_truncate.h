#include "../../../src/func/filter/truncate.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/add.h"
#include "../../../src/func/op/mul.h"
#include "../../../src/func/op/step.h"
#include "../../../src/func/op/sum.h"
#include "../../util/test.h"

void test_truncate_miss()
{
    func time = sum_create(const_(0.1));
    func rect1 = mul_create(FUNCS(step_create(const_(0), time), step_create(time, const_(0.09))));
    func rect2 = mul_create(FUNCS(step_create(const_(0.5), time), step_create(time, const_(0.59))));
    Func *input = add_create(FUNCS(rect1, rect2));
    Func *trunc = truncate_create(const_(1.25), input);
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

void test_truncate_hit()
{
    func time = sum_create(const_(0.1));
    func rect1 = mul_create(FUNCS(step_create(const_(0), time), step_create(time, const_(0.09))));
    func rect2 = mul_create(FUNCS(step_create(const_(0.8), time), step_create(time, const_(0.89))));
    Func *input = add_create(FUNCS(rect1, rect2));
    Func *trunc = truncate_create(const_(1.25), input);
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

void test_truncate()
{
    test_truncate_miss();
    test_truncate_hit();
    func_free();
}

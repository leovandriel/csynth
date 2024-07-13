#include "../../../src/func/filter/chorus.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/sine.h"
#include "../../util/test.h"

void test_chorus()
{
    Gen *gen = gen_create(chorus_create(const_(0.1), sine_create(const_(0.02)), const_(0.2), const_(0.2), sine_create(const_(1))));
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    gen_free(gen);
    func_free();
}

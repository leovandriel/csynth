#include "../../../src/func/filter/chorus.h"
#include "../../../src/func/filter/filters.h"
#include "../../../src/func/gen/gens.h"
#include "../../util/test.h"

void test_chorus()
{
    Gen *gen = gen_create(chorus_(sine_(0.2), 0.2, 0.2, sine_(10)));
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    gen_free(gen);
    func_free();
}

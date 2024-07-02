#include "../../../src/func/effect/unison.h"
#include "../../../src/func/gen/saw.h"
#include "../../util/test.h"

void test_unison()
{
    rand_seed(0);
    Func *time = pitch_(0.1, unison_(5, 0.1, saw_(1)));
    Gen *gen = gen_create(time);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, eval), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, eval), 0.0212456065397963);
    assert_double_equal(gen_eval(gen, eval), 0.0424912130795926);
    assert_double_equal(gen_eval(gen, eval), 0.0637368196193888);
    assert_double_equal(gen_eval(gen, eval), 0.0849824261591851);
    assert_double_equal(gen_eval(gen, eval), 0.1062280326989814);
    assert_double_equal(gen_eval(gen, eval), 0.1274736392387776);
    assert_double_equal(gen_eval(gen, eval), 0.1487192457785740);
    assert_double_equal(gen_eval(gen, eval), 0.1699648523183702);
    assert_double_equal(gen_eval(gen, eval), 0.1912104588581665);
    assert_double_equal(gen_eval(gen, eval), 0.2124560653979627);
    assert_double_equal(gen_eval(gen, eval), 0.2337016719377590);
    gen_free(gen);
    func_free();
}

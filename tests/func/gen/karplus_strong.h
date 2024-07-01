#include "../../../src/func/gen/gens.h"
#include "../../../src/func/gen/karplus_strong.h"
#include "../../util/test.h"

void test_karplus_strong()
{
    rand_seed(0);
    Func *time = karplus_strong_(const_(2), 0.5);
    Gen *gen = gen_create(time);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, eval), -0.1657808658808207);
    assert_double_equal(gen_eval(gen, eval), 0.2821309923619489);
    assert_double_equal(gen_eval(gen, eval), 0.2409750432587839);
    assert_double_equal(gen_eval(gen, eval), 0.2436252445284819);
    assert_double_equal(gen_eval(gen, eval), 0.1903687808971684);
    assert_double_equal(gen_eval(gen, eval), 0.0290875316202821);
    assert_double_equal(gen_eval(gen, eval), 0.1307765089051832);
    assert_double_equal(gen_eval(gen, eval), 0.1211500719468165);
    assert_double_equal(gen_eval(gen, eval), 0.1084985063564126);
    assert_double_equal(gen_eval(gen, eval), 0.0548640781293626);
    assert_double_equal(gen_eval(gen, eval), 0.0399660101313663);
    assert_double_equal(gen_eval(gen, eval), 0.0629816452129999);
    gen_free(gen);
    func_free();
}

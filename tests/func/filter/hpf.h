#include "../../../src/func/filter/hpf.h"
#include "../../util/test.h"

void test_hpf()
{
    Func *time = hpf(const_(1), const_(10));
    Gen *gen = gen_create(time);
    Eval eval = {.step = {0.1, 0.1}};
    assert_double_equal(gen_eval(gen, eval), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, eval), 0.1373025616984130);
    assert_double_equal(gen_eval(gen, eval), 0.0188519934489465);
    assert_double_equal(gen_eval(gen, eval), 0.0025884269936620);
    assert_double_equal(gen_eval(gen, eval), 0.0003553976569991);
    assert_double_equal(gen_eval(gen, eval), 0.0000487970087276);
    assert_double_equal(gen_eval(gen, eval), 0.0000066999543015);
    assert_double_equal(gen_eval(gen, eval), 0.0000009199208889);
    assert_double_equal(gen_eval(gen, eval), 0.0000001263074946);
    assert_double_equal(gen_eval(gen, eval), 0.0000000173423426);
    assert_double_equal(gen_eval(gen, eval), 0.0000000023811481);
    assert_double_equal(gen_eval(gen, eval), 0.0000000003269377);
    gen_free(gen);
    func_free();
}

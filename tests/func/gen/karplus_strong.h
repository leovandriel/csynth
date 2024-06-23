#include "../../../src/func/gen/karplus_strong.h"
#include "../../util/test.h"

void test_karplus_strong()
{
    rand_seed(0);
    Func *time = karplus_strong_(const_(2), 0.5);
    Gen *gen = gen_create(time);
    Eval eval = {.delta = 0.1};
    assert_double_equal(gen_eval(gen, eval), -0.2886412523525353);
    assert_double_equal(gen_eval(gen, eval), 0.4912185886479782);
    assert_double_equal(gen_eval(gen, eval), 0.4195619192984845);
    assert_double_equal(gen_eval(gen, eval), 0.4241761877148519);
    assert_double_equal(gen_eval(gen, eval), 0.2779732095631874);
    assert_double_equal(gen_eval(gen, eval), 0.0881769071115131);
    assert_double_equal(gen_eval(gen, eval), 0.3964402421159615);
    assert_double_equal(gen_eval(gen, eval), 0.3672583421674327);
    assert_double_equal(gen_eval(gen, eval), 0.3056282766592155);
    assert_double_equal(gen_eval(gen, eval), 0.1593760951610511);
    assert_double_equal(gen_eval(gen, eval), 0.2109418661214700);
    assert_double_equal(gen_eval(gen, eval), 0.3324191163681807);
    gen_free(gen);
    func_free();
}

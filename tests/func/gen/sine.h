#include "../../../src/func/gen/sine.h"
#include "../../../src/func/gen/timer.h"
#include "../../util/test.h"

void test_sine_const()
{
    Func *time = sine(const_(1));
    Gen *gen = gen_create(time);
    Eval eval = {.delta = 0.1};
    assert_double_equal(gen_eval(gen, eval), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, eval), 0.5877852522924731);
    assert_double_equal(gen_eval(gen, eval), 0.9510565162951535);
    assert_double_equal(gen_eval(gen, eval), 0.9510565162951536);
    assert_double_equal(gen_eval(gen, eval), 0.5877852522924732);
    assert_double_equal(gen_eval(gen, eval), 0.0000000000000001);
    assert_double_equal(gen_eval(gen, eval), -0.5877852522924730);
    assert_double_equal(gen_eval(gen, eval), -0.9510565162951535);
    assert_double_equal(gen_eval(gen, eval), -0.9510565162951536);
    assert_double_equal(gen_eval(gen, eval), -0.5877852522924734);
    assert_double_equal(gen_eval(gen, eval), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, eval), 0.5877852522924731);
    gen_free(gen);
}

void test_sine_timer()
{
    Func *time = sine(timer());
    Gen *gen = gen_create(time);
    Eval eval = {.delta = 0.1};
    assert_double_equal(gen_eval(gen, eval), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, eval), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, eval), 0.0314107590781283);
    assert_double_equal(gen_eval(gen, eval), 0.1045284632676535);
    assert_double_equal(gen_eval(gen, eval), 0.2181432413965426);
    assert_double_equal(gen_eval(gen, eval), 0.3681245526846780);
    assert_double_equal(gen_eval(gen, eval), 0.5446390350150272);
    assert_double_equal(gen_eval(gen, eval), 0.7289686274214117);
    assert_double_equal(gen_eval(gen, eval), 0.8910065241883679);
    assert_double_equal(gen_eval(gen, eval), 0.9892723329629883);
    assert_double_equal(gen_eval(gen, eval), 0.9759167619387474);
    assert_double_equal(gen_eval(gen, eval), 0.8090169943749475);
    gen_free(gen);
}

void test_sine()
{
    test_sine_const();
    test_sine_timer();
    func_free();
}

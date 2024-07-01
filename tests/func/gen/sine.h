#include "../../../src/func/gen/gens.h"
#include "../../../src/func/gen/sine.h"
#include "../../../src/func/time/ticker.h"
#include "../../../src/func/time/times.h"
#include "../../util/test.h"

void test_sine_const()
{
    Func *time = sine_create(pitch_ticker_(1));
    Gen *gen = gen_create(time);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, eval), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, eval), 0.5877852522924731);
    assert_double_equal(gen_eval(gen, eval), 0.9510565162951535);
    assert_double_equal(gen_eval(gen, eval), 0.9510565162951536);
    assert_double_equal(gen_eval(gen, eval), 0.5877852522924732);
    assert_double_equal(gen_eval(gen, eval), 0.0000000000000001);
    assert_double_equal(gen_eval(gen, eval), -0.5877852522924730);
    assert_double_equal(gen_eval(gen, eval), -0.9510565162951535);
    assert_double_equal(gen_eval(gen, eval), -0.9510565162951536);
    assert_double_equal(gen_eval(gen, eval), -0.5877852522924740);
    assert_double_equal(gen_eval(gen, eval), -0.0000000000000011);
    assert_double_equal(gen_eval(gen, eval), 0.5877852522924724);
    gen_free(gen);
}

void test_sine_timer()
{
    Func *time = sine(pitch_timer_(1));
    Gen *gen = gen_create(time);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, eval), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, eval), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, eval), 0.0627905195293134);
    assert_double_equal(gen_eval(gen, eval), 0.1873813145857247);
    assert_double_equal(gen_eval(gen, eval), 0.3681245526846780);
    assert_double_equal(gen_eval(gen, eval), 0.5877852522924732);
    assert_double_equal(gen_eval(gen, eval), 0.8090169943749475);
    assert_double_equal(gen_eval(gen, eval), 0.9685831611286311);
    assert_double_equal(gen_eval(gen, eval), 0.9822872507286886);
    assert_double_equal(gen_eval(gen, eval), 0.7705132427757893);
    assert_double_equal(gen_eval(gen, eval), 0.3090169943749471);
    assert_double_equal(gen_eval(gen, eval), -0.3090169943749477);
    gen_free(gen);
}

void test_sine()
{
    test_sine_const();
    test_sine_timer();
    func_free();
}

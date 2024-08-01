#include "../../../src/func/control/pause.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/saw.h"
#include "../../util/test.h"

void test_pause(void)
{
    Gen *gen = gen_create(pause_create(1, 0, 0, saw_create(const_create(0.1))));
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.2000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.4000000000000000);
    control_event_broadcast_keyboard(0.0, 1);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    control_event_broadcast_keyboard(0.0, 1);
    assert_double_equal(gen_eval(gen, NULL), 0.6000000000000001);
    assert_double_equal(gen_eval(gen, NULL), 0.8000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 1.0000000000000001);
    gen_free(gen);
    func_free();
    event_free();
}

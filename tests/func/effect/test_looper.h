#include "../../../src/event/control_event.h"
#include "../../../src/func/effect/looper.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/saw.h"
#include "../../util/test.h"

void test_looper(void)
{
    Gen *gen = gen_create(looper_keyboard_create(1, const_create(0.2), saw_create(const_create(0.1))));
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    control_event_broadcast_keyboard(0.0, 1);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.2000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.4000000000000000);
    control_event_broadcast_keyboard(0.0, 1);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.2000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.4000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.2000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.4000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    gen_free(gen);
    func_free();
    event_free();
}

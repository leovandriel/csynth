#include "../../../src/func/control/key.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/saw.h"
#include "../../util/test.h"

void test_key(void)
{
    Gen *gen = gen_create(key_create(1, 2, saw_create(const_create(0.1))));
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    control_event_broadcast_midi(0.0, MidiTypeNoteOn, 0, 2, 64);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.2000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.4000000000000000);
    control_event_broadcast_midi(0.0, MidiTypeNoteOff, 0, 2, 0);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    gen_free(gen);
    func_free();
    event_free();
}

#include "../../../src/func/control/pad.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/saw.h"
#include "../../util/test.h"

void test_pad(void)
{
    Gen *gen = gen_create(pad_create(1, 2, saw_create(const_create(0.1))));
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    control_event_broadcast_midi(0.0, MidiTypeNoteOn, 0, 2, 127);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.2000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.4000000000000000);
    control_event_broadcast_midi(0.0, MidiTypeNoteOn, 0, 2, 1);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0015748031496063);
    assert_double_equal(gen_eval(gen, NULL), 0.0031496062992126);
    gen_free(gen);
    func_free();
    event_free();
}

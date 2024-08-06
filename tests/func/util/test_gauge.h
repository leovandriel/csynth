#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/sum.h"
#include "../../../src/func/util/gauge.h"
#include "../../util/test.h"

static size_t test_gauge_flag_global = 0;

void handle(StateEvent *event, __U void *context)
{
    assert_long_equal(event->key_type, StateEventKeyTypeLabel);
    assert_string_equal(event->key, "test");
    assert_long_equal(event->value_type, StateEventValueTypeDouble);
    assert_double_equal(*(double *)event->value, 0.1);
    test_gauge_flag_global++;
}

void test_gauge(void)
{
    StateEventContext context = {
        .handler = NULL,
        .handle_event = handle,
    };
    state_event_add(&context);
    Gen *gen = gen_create(gauge_create("test", const_create(0.1), sum_create(const_create(0.1))));
    Eval eval = {0};
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.1);
    assert_double_equal(gen_eval(gen, &eval), 0.2);
    assert_double_equal(gen_eval(gen, &eval), 0.3);
    assert_long_equal(test_gauge_flag_global, 1);
    gen_free(gen);
    func_free();
    event_free();
}

#define ALLOC_TRACE
#include "../../../src/func/gen/const.h"
#include "../../../src/func/util/mem.h"
#include "../../util/test.h"

static size_t test_mem_flag_global = 0;

void handle(StateEvent *event, __U void *context)
{
    assert_long_equal(event->key_type, StateEventKeyTypeLabel);
    assert_long_equal(event->value_type, StateEventValueTypeSize);
    if (strcmp((const char *)event->key, "alloc") == 0)
    {
        assert_long_equal(*(size_t *)event->value, 280);
    }
    else
    {
        assert_long_equal(*(size_t *)event->value, 0);
    }
    test_mem_flag_global++;
}

void test_mem()
{
    StateEventContext context = {
        .handler = NULL,
        .handle_event = handle,
    };
    state_event_add(&context);
    Func *input = mem_create(const_(0));
    Gen *gen = gen_create(input);
    Eval eval = {.wall_tick = 0.1};
    gen_eval(gen, &eval);
    assert_long_equal(test_mem_flag_global, 2);
    gen_free(gen);
    func_free();
    event_clear();
}

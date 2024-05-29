//
// select.h - Trigger based on key select
//
#ifndef CSYNTH_SELECT_H
#define CSYNTH_SELECT_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/key_event.h"
#include "../../util/state_event.h"

typedef struct
{
    KeyEventContext parent;
    int key;
    int count;
    int selected;
} SelectContext;

static double select_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    SelectContext *context = (SelectContext *)context_;
    return gen_eval(args[context->selected]);
}

int select_listener(int key, void *context_)
{
    SelectContext *context = (SelectContext *)context_;
    if (key == context->key)
    {
        context->selected = (context->selected + 1) % context->count;
        state_event_broadcast(context->key, StateEventTypeInt, &context->selected);
    }
    return 0;
}

void select_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    SelectContext *context = (SelectContext *)context_;
    state_event_broadcast(context->key, StateEventTypeInt, &context->selected);
    key_event_add(&context->parent);
}

Func *select_args(int key, int count, ...)
{
    va_list valist;
    va_start(valist, count);
    SelectContext initial = (SelectContext){
        .parent = {.key_listener = select_listener},
        .key = key,
        .count = count,
    };
    Func *func = func_create_va(select_init, select_eval, key_event_free, sizeof(SelectContext), &initial, FUNC_FLAG_SKIP_RESET, count, valist);
    va_end(valist);
    return func;
}

#define select(key, ...) (select_args(key, (sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))

Func *select_array(int key, int count, Func **args)
{
    SelectContext initial = (SelectContext){
        .parent = {.key_listener = select_listener},
        .key = key,
        .count = count,
    };
    return func_create_array(select_init, select_eval, key_event_free, sizeof(SelectContext), &initial, FUNC_FLAG_SKIP_RESET, count, args);
}

#endif // CSYNTH_SELECT_H

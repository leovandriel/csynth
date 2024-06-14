//
// selector.h - Trigger based on key select
//
#ifndef CSYNTH_SELECTOR_H
#define CSYNTH_SELECTOR_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/key_event.h"
#include "../../event/state_event.h"

typedef struct
{
    KeyEventContext parent;
    int key;
    int count;
    int selected;
} SelectorContext;

static double selector_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    SelectorContext *context = (SelectorContext *)context_;
    return gen_eval(args[context->selected]);
}

int selector_listener(int key, void *context_)
{
    SelectorContext *context = (SelectorContext *)context_;
    if (key == context->key)
    {
        context->selected = (context->selected + 1) % context->count;
        state_event_broadcast(context->key, StateEventTypeInt, &context->selected);
    }
    return 0;
}

void selector_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    SelectorContext *context = (SelectorContext *)context_;
    state_event_broadcast(context->key, StateEventTypeInt, &context->selected);
    key_event_add(&context->parent);
}

Func *selector_args(int key, int count, ...)
{
    va_list valist = {0};
    va_start(valist, count);
    SelectorContext initial = (SelectorContext){
        .parent = {.key_listener = selector_listener},
        .key = key,
        .count = count,
    };
    Func *func = func_create_va(selector_init, selector_eval, key_event_free, sizeof(SelectorContext), &initial, FUNC_FLAG_SKIP_RESET, count, valist);
    va_end(valist);
    return func;
}

#define selector(key, ...) (selector_args(key, (sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))

Func *selector_array(int key, int count, Func **args)
{
    SelectorContext initial = (SelectorContext){
        .parent = {.key_listener = selector_listener},
        .key = key,
        .count = count,
    };
    return func_create_array(selector_init, selector_eval, key_event_free, sizeof(SelectorContext), &initial, FUNC_FLAG_SKIP_RESET, count, args);
}

#endif // CSYNTH_SELECTOR_H

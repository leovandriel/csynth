//
// selector.h - Trigger based on key select
//
#ifndef CSYNTH_SELECTOR_H
#define CSYNTH_SELECTOR_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/keyboard_event.h"
#include "../../event/state_event.h"

typedef struct
{
    KeyboardEventContext parent;
    int key;
    int count;
    int selected;
} SelectorContext;

static double selector_eval(__U int count, __U Gen **args, Eval eval, void *context_)
{
    SelectorContext *context = (SelectorContext *)context_;
    return gen_eval(args[context->selected], eval);
}

static void selector_handle_event(int key, void *context_)
{
    SelectorContext *context = (SelectorContext *)context_;
    if (key == context->key)
    {
        context->selected = (context->selected + 1) % context->count;
        state_event_broadcast(StateEventKeyTypeKeyboard, &context->key, StateEventValueTypeInt, &context->selected);
    }
}

static int selector_init(__U int count, __U Gen **args, void *context_)
{
    SelectorContext *context = (SelectorContext *)context_;
    state_event_broadcast(StateEventKeyTypeKeyboard, &context->key, StateEventValueTypeInt, &context->selected);
    csError error = keyboard_event_add(&context->parent);
    return error_catch(error);
}

Func *selector_args(int key, int count, ...)
{
    va_list valist = {0};
    va_start(valist, count);
    SelectorContext initial = (SelectorContext){
        .parent = {.handle_event = selector_handle_event},
        .key = key,
        .count = count,
    };
    Func *output = func_create_va(selector_init, selector_eval, keyboard_event_free, sizeof(SelectorContext), &initial, FuncFlagSkipReset, count, valist);
    va_end(valist);
    return output;
}

#define selector(key, ...) (selector_args(key, (sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))

Func *selector_array(int key, int count, Func **args)
{
    SelectorContext initial = (SelectorContext){
        .parent = {.handle_event = selector_handle_event},
        .key = key,
        .count = count,
    };
    return func_create_array(selector_init, selector_eval, keyboard_event_free, sizeof(SelectorContext), &initial, FuncFlagSkipReset, count, args);
}

#endif // CSYNTH_SELECTOR_H

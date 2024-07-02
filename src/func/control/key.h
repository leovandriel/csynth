//
// key.h - Trigger based on key trigger
//
#ifndef CSYNTH_KEY_H
#define CSYNTH_KEY_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"

typedef struct
{
    ControlEventContext parent;
    ControlEventKey key;
    int active;
    int reset;
} KeyContext;

static double key_eval(__U int count, __U Gen **args, Eval eval, void *context_)
{
    KeyContext *context = (KeyContext *)context_;
    if (context->reset != 0)
    {
        gen_reset(args[0]);
        context->reset = 0;
    }
    if (context->active != 0)
    {
        double input = gen_eval(args[0], eval);
        return input * (double)context->active / 64.0;
    }
    return 0.;
}

static void key_handle_event(ControlEvent *event, void *context_)
{
    KeyContext *context = (KeyContext *)context_;
    if (control_event_key_equal(event->key, context->key))
    {
        context->active = (int)event->key.midi.data2;
        context->reset = event->key.midi.data2 ? 1 : 0;
    }
}

static int key_init(__U int count, __U Gen **args, void *context_)
{
    KeyContext *context = (KeyContext *)context_;
    csError error = control_event_add(&context->parent);
    return error_catch(error);
}

Func *key_create(int channel, int pitch, Func *input)
{
    KeyContext initial = {
        .parent = {.handle_event = key_handle_event},
        .key = {
            .type = ControlEventTypeMidi,
            .midi = {
                .type = MidiTypeNoteOff,
                .channel = channel - 1,
                .data1 = pitch,
            }},
    };
    return func_create(key_init, key_eval, control_event_free, sizeof(KeyContext), &initial, FuncFlagNone, FUNCS(input));
}

#endif // CSYNTH_KEY_H

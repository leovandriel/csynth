//
// key.h - Trigger based on key trigger
//
#ifndef CSYNTH_KEY_H
#define CSYNTH_KEY_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/midi_event.h"

typedef struct
{
    MidiEventContext parent;
    MidiKey key;
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
        return gen_eval(args[0], eval) * (double)context->active / 64.0;
    }
    return 0.;
}

static void key_handle_event(__U double time, MidiType type, uint8_t channel, uint8_t data1, uint8_t data2, void *context_)
{
    KeyContext *context = (KeyContext *)context_;
    if ((type == MidiTypeNoteOff || type == MidiTypeNoteOn) && channel == context->key.channel && data1 == context->key.control)
    {
        context->active = (int)data2;
        context->reset = data2 ? 1 : 0;
    }
}

static int key_init(__U int count, __U Gen **args, void *context_)
{
    KeyContext *context = (KeyContext *)context_;
    csError error = midi_event_add(&context->parent);
    return error_catch(error);
}

Func *key(int channel, int pitch, Func *func)
{
    KeyContext initial = (KeyContext){
        .parent = {.handle_event = key_handle_event},
        .key = (MidiKey){
            .channel = channel - 1,
            .control = pitch,
        },
    };
    return func_create(key_init, key_eval, midi_event_free, sizeof(KeyContext), &initial, FuncFlagNone, 1, func);
}

#endif // CSYNTH_KEY_H

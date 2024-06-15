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
    uint32_t key;
    uint32_t channel;
    int active;
    int reset;
} KeyContext;

static double key_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    KeyContext *context = (KeyContext *)context_;
    if (context->reset)
    {
        gen_reset(args[0]);
        context->reset = 0;
    }
    if (context->active)
    {
        return gen_eval(args[0]) * (double)context->active / 64.0;
    }
    return 0.;
}

int key_listener(__attribute__((unused)) double time, MidiType type, uint32_t channel, uint32_t data1, uint32_t data2, void *context_)
{
    KeyContext *context = (KeyContext *)context_;
    if ((type == MidiTypeNoteOff || type == MidiTypeNoteOn) && channel == context->channel && data1 == context->key)
    {
        context->active = (int)data2;
        context->reset = data2 ? 1 : 0;
    }
    return 0;
}

void key_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    KeyContext *context = (KeyContext *)context_;
    midi_event_add(&context->parent);
}

Func *key(int key, int channel, Func *func)
{
    KeyContext initial = (KeyContext){
        .parent = {.midi_listener = key_listener},
        .key = key,
        .channel = channel,
    };
    return func_create(key_init, key_eval, midi_event_free, sizeof(KeyContext), &initial, FUNC_FLAG_DEFAULT, 1, func);
}

#endif // CSYNTH_KEY_H

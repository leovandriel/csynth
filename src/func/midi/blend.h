//
// blend.h - Pitch blend
//
#ifndef CSYNTH_BLEND_H
#define CSYNTH_BLEND_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/midi_event.h"
#include "../../event/state_event.h"

typedef struct
{
    MidiEventContext parent;
    MidiKey key;
    double value;
} BlendContext;

static double blend_eval(__U int count, __U Gen **args, Eval eval, void *context_)
{
    BlendContext *context = (BlendContext *)context_;
    double factor = gen_eval(args[0], eval);
    eval.tick[EvalTickPitch] *= pow(factor, context->value);
    double input = gen_eval(args[1], eval);
    return input;
}

static void blend_handle_event(__U double time, MidiType type, uint8_t channel, uint8_t data1, uint8_t data2, void *context_)
{
    BlendContext *context = (BlendContext *)context_;
    if (type == MidiTypePitchBend && channel == context->key.channel)
    {
        uint16_t data = ((uint16_t)data2 << 7) | data1;
        context->value = 2.0 * (double)data / 16383.0 - 1;
    }
}

static int blend_init(__U int count, __U Gen **args, void *context_)
{
    BlendContext *context = (BlendContext *)context_;
    csError error = midi_event_add(&context->parent);
    return error_catch(error);
}

Func *blend_create(int channel, Func *factor, Func *input)
{
    BlendContext initial = {
        .parent = {.handle_event = blend_handle_event},
        .key = {.channel = channel - 1},
    };
    return func_create(blend_init, blend_eval, midi_event_free, sizeof(BlendContext), &initial, FuncFlagNone, FUNCS(factor, input));
}

#endif // CSYNTH_BLEND_H

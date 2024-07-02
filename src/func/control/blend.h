//
// blend.h - Pitch blend
//
#ifndef CSYNTH_BLEND_H
#define CSYNTH_BLEND_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"
#include "../../event/state_event.h"

typedef struct
{
    ControlEventContext parent;
    ControlEventKey key;
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

static void blend_handle_event(ControlEvent event, void *context_)
{
    BlendContext *context = (BlendContext *)context_;
    if (control_event_key_equal(event.key, context->key))
    {
        uint16_t data = ((uint16_t)event.key.midi.data2 << 7) | event.key.midi.data1;
        context->value = 2.0 * (double)data / 16383.0 - 1;
    }
}

static int blend_init(__U int count, __U Gen **args, void *context_)
{
    BlendContext *context = (BlendContext *)context_;
    csError error = control_event_add(&context->parent);
    return error_catch(error);
}

Func *blend_create(int channel, Func *factor, Func *input)
{
    BlendContext initial = {
        .parent = {.handle_event = blend_handle_event},
        .key = {
            .type = ControlEventTypeMidi,
            .midi = {
                .type = MidiTypePitchBend,
                .channel = channel - 1,
            },
        },
    };
    return func_create(blend_init, blend_eval, control_event_free, sizeof(BlendContext), &initial, FuncFlagNone, FUNCS(factor, input));
}

#endif // CSYNTH_BLEND_H

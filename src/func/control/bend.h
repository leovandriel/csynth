//
// bend.h - Pitch bend
//
#ifndef CSYNTH_BEND_H
#define CSYNTH_BEND_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../ui/midi_state.h"

typedef struct
{
    uint8_t channel;
} BendContext;

static double bend_eval(__U int count, __U Gen **args, Eval *eval, void *context_)
{
    BendContext *context = (BendContext *)context_;
    double factor = gen_eval(args[0], eval);
    double value = midi_state_get(MidiTypePitchBend, context->channel, 0);
    double restore = eval->tick[EvalTickPitch];
    eval->tick[EvalTickPitch] = restore * pow(factor, value);
    double input = gen_eval(args[1], eval);
    eval->tick[EvalTickPitch] = restore;
    return input;
}

Func *bend_create(int channel, Func *factor, Func *input)
{
    BendContext initial = {
        .channel = channel - 1,
    };
    return func_create(NULL, bend_eval, NULL, sizeof(BendContext), &initial, FuncFlagNone, FUNCS(factor, input));
}

#endif // CSYNTH_BEND_H

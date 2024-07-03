//
// fps.h - Display function evals per sample
//
#ifndef CSYNTH_FPS_H
#define CSYNTH_FPS_H

#include <stdio.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/state_event.h"
#include "../../util/error.h"

typedef struct
{
    double time;
    size_t gen_count;
    size_t sample_count;
    const char *label;
} FpsContext;

static double fps_eval(__U int count, Gen **args, Eval *eval, void *context_)
{
    FpsContext *context = (FpsContext *)context_;
    size_t gen_count = eval->gen_count;
    double input = gen_eval(args[0], eval);
    size_t diff = eval->gen_count - gen_count;
    if (context->time >= 1.0)
    {
        double fps = (double)context->gen_count / (double)context->sample_count;
        state_event_broadcast(eval->wall_time, StateEventKeyTypeLabel, context->label, StateEventValueTypeDouble, &fps);
        context->time = 0;
        context->gen_count = 0;
        context->sample_count = 0;
    }
    context->time += eval->wall_tick;
    context->gen_count += diff;
    context->sample_count++;
    return input;
}

Func *fps_create(const char *label, Func *input)
{
    FpsContext initial = {
        .label = label,
        .time = .99,
    };
    return func_create(NULL, fps_eval, NULL, sizeof(FpsContext), &initial, FuncFlagNone, FUNCS(input));
}

#endif // CSYNTH_FPS_H

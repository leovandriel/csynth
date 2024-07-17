//
// actuate.h - Simulate key press
//
#ifndef CSYNTH_ACTUATE_H
#define CSYNTH_ACTUATE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"

typedef struct
{
    int key;
    bool completed;
} ActuateContext;

static double actuate_eval(__U size_t count, __U Gen **args, __U Eval *eval, void *context_)
{
    ActuateContext *context = (ActuateContext *)context_;
    if (!context->completed)
    {
        control_event_broadcast_keyboard(eval->wall_time, context->key);
        context->completed = true;
    }
    return 0.0;
}

Func *actuate_create(int key)
{
    ActuateContext initial = {.key = key};
    return func_create(NULL, actuate_eval, NULL, sizeof(ActuateContext), &initial, FuncFlagNone, );
}

#endif // CSYNTH_ACTUATE_H

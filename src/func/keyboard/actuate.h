//
// actuate.h - Simulate key press
//
#ifndef CSYNTH_ACTUATE_H
#define CSYNTH_ACTUATE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/keyboard_event.h"
#include "../../util/time.h"

typedef struct
{
    int key;
    int completed;
} ActuateContext;

static double actuate_eval(__U int count, __U Gen **args, __U double delta, void *context_)
{
    ActuateContext *context = (ActuateContext *)context_;
    if (!context->completed)
    {
        keyboard_event_broadcast(time_wall(), context->key);
        context->completed = 1;
    }
    return 0.0;
}

Func *actuate(int key)
{
    ActuateContext initial = (ActuateContext){
        .key = key,
    };
    return func_create(NULL, actuate_eval, NULL, sizeof(ActuateContext), &initial, FUNC_FLAG_DEFAULT, 0);
}

#endif // CSYNTH_ACTUATE_H

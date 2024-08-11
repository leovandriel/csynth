#ifndef CSYNTH_ACTUATE_H
#define CSYNTH_ACTUATE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"

/** @see actuate_create */
typedef struct
{
    /** @brief Keyboard key code to be broadcasted; can be char. */
    int key;
    /** @brief Flag indicating the key has been broadcasted. */
    bool completed;
} ActuateContext;

static double actuate_eval(__U size_t count, __U Gen **args, __U Eval *eval, void *context_)
{
    ActuateContext *context = (ActuateContext *)context_;
    if (!context->completed && eval != NULL)
    {
        control_event_broadcast_keyboard(eval->wall_time, context->key);
        context->completed = true;
    }
    return 0.0;
}

/**
 * @brief Create a function that broadcasts a key event once, simulating a key
 * press.
 *
 * @param key The key code to be broadcasted, can be char, e.g. ' '.
 * @return Func* Actuate function.
 */
Func *actuate_create(int key)
{
    ActuateContext initial = {.key = key};
    return func_create(NULL, actuate_eval, NULL, NULL, sizeof(ActuateContext), &initial, FuncFlagNone);
}

#endif // CSYNTH_ACTUATE_H

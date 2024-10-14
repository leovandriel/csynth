#ifndef CSYNTH_REPLAY_H
#define CSYNTH_REPLAY_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"
#include "../../mem/key_list.h"

/** @see replay_create */
typedef struct
{
    /** @brief Linked list of keyboard events. */
    KeyList list;
    /** @brief Current event, awaiting to be broadcasted. */
    KeyboardEvent *current;
    /** @brief Current time of the replay. */
    double time;
} ReplayContext;

static double replay_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    ReplayContext *context = (ReplayContext *)context_;
    while (context->current && context->current->time <= context->time)
    {
        control_event_broadcast_keyboard(context->current->time, context->current->key);
        context->current = context->current->next;
    }
    double tick = gen_eval(args[0], eval);
    double input = gen_eval(args[1], eval);
    context->time += tick;
    return input;
}

static void replay_cleanup(void *initial_)
{
    ReplayContext *initial = (ReplayContext *)initial_;
    key_list_clear(&initial->list);
}

/**
 * @brief Create a function that replays a keyboard events, emulating key
 * presses.
 *
 * @param list List of key events.
 * @param tick Function to determine the time between key presses.
 * @param input Input function to trigger.
 * @return Func* Replay function.
 */
Func *replay_create(KeyList list, Func *tick, Func *input)
{
    ReplayContext initial = {
        .list = list,
        .current = list.head,
    };
    return func_create(NULL, replay_eval, NULL, replay_cleanup, sizeof(ReplayContext), &initial, FuncFlagNone, tick, input);
}

/**
 * @brief Create a function that replays a keyboard event file, emulating key
 * presses.
 *
 * @param file File handle of the replay file.
 * @param tick Function to determine the time between key presses.
 * @param input Input function to trigger.
 * @return Func* Replay function.
 */
Func *replay_create_file(FILE *file, Func *tick, Func *input)
{
    KeyList list = {0};
    if (key_list_read_file(&list, file) != csErrorNone)
    {
        return NULL;
    }
    return replay_create(list, tick, input);
}

/**
 * @brief Create a function that replays a keyboard event file, emulating key
 * presses.
 *
 * @param filename Filename of the replay file.
 * @param tick Function to determine the time between key presses.
 * @param input Input function to trigger.
 * @return Func* Replay function.
 */
Func *replay_create_filename(const char *filename, Func *tick, Func *input)
{
    KeyList list = {0};
    if (key_list_read_filename(&list, filename) != csErrorNone)
    {
        return NULL;
    }
    return replay_create(list, tick, input);
}

#endif // CSYNTH_REPLAY_H

#ifndef CSYNTH_RUN_H
#define CSYNTH_RUN_H

#include <stddef.h>
#include <unistd.h>

#include "../util/cleanup.h"
#include "../util/error.h"

typedef enum
{
    csBreak = -1,  // Stop looping
    csContinue = 0 // Continue looping
} csRun;

typedef union
{
    csRun run;
    csError error;
} csRunOrError;

typedef csError (*run_loop_init_cb)(void *context);
typedef csRunOrError (*run_loop_tick_cb)(void *context);
typedef void (*run_loop_free_cb)(void *context);

typedef struct
{
    run_loop_init_cb init;
    run_loop_tick_cb tick;
    run_loop_free_cb free;
    void *context;
    bool manage_context;
} RunLoop;

csError run_loop_run(size_t count, RunLoop *loops)
{
    for (size_t i = 0; i < count; i++)
    {
        if (loops[i].init)
        {
            csError error = csErrorNone;
            if (loops[i].manage_context && loops[i].context == NULL)
            {
                error = error_type_message(csErrorMemoryAlloc, "Null context for run loop");
            }
            else
            {
                error = loops[i].init(loops[i].context);
            }
            if (error != csErrorNone)
            {
                // cleanup already initialized loops
                for (size_t j = 0; j < i; j++)
                {
                    if (loops[j].free)
                    {
                        loops[j].free(loops[j].context);
                    }
                }
                return error_type_message(error, "Unable to initialize run loop");
            }
        }
    }
    csRunOrError result = {.run = csContinue};
    for (__U size_t j = 0; result.run == csContinue; j++)
    {
        {
            for (size_t i = 0; i < count && result.run == csContinue; i++)
                if (loops[i].tick)
                {
                    result = loops[i].tick(loops[i].context);
                }
        }
#ifdef AUTO_EXIT
        if (j >= AUTO_EXIT)
        {
            result = (csRunOrError){.run = csBreak};
        }
#endif
    }
    for (size_t i = 0; i < count; i++)
    {
        if (loops[i].free)
        {
            loops[i].free(loops[i].context);
            if (loops[i].manage_context)
            {
                free_(loops[i].context);
            }
        }
    }
    return result.error < csErrorNone ? result.error : csErrorNone;
}

csError run_loop_run_cleanup(size_t count, RunLoop *loops)
{
    csError error = run_loop_run(count, loops);
    cleanup_all();
    return error;
}

#define run_loop(...) (run_loop_run_cleanup(ARGS_TYPE(RunLoop, __VA_ARGS__)))

#endif // CSYNTH_RUN_H

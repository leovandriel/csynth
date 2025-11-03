#ifndef CSYNTH_SLEEP_RUN_H
#define CSYNTH_SLEEP_RUN_H

#include <unistd.h>

#include "../util/error.h"
#include "../util/time.h"
#include "./run.h"

typedef struct
{
    double duration;
} SleeperRun;

csError sleeper_run_init(void *context)
{
    SleeperRun *run = (SleeperRun *)context;
    if (run == NULL)
    {
        return error_type_message(csErrorMemoryAlloc, "Unable to allocate memory for sleeper run");
    }
    return csErrorNone;
}

csError sleeper_run_tick(void *context)
{
    SleeperRun *run = (SleeperRun *)context;
    time_sleep(run->duration);
    return csErrorNone;
}

void sleeper_run_free(void *context)
{
    free_(context);
}

RunLoop sleeper_run(double duration)
{
    SleeperRun *run = (SleeperRun *)malloc_(sizeof(SleeperRun));
    if (run != NULL)
    {
        run->duration = duration;
    }
    return (RunLoop){
        .init = sleeper_run_init,
        .tick = sleeper_run_tick,
        .free = sleeper_run_free,
        .context = run,
    };
}

#endif // CSYNTH_SLEEP_RUN_H

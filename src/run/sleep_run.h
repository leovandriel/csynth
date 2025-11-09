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

csRunOrError sleep_run_tick(void *context)
{
    SleeperRun *run = (SleeperRun *)context;
    time_sleep(run->duration);
    return (csRunOrError){.run = csContinue};
}

RunLoop sleep_run(double duration)
{
    SleeperRun *run = (SleeperRun *)malloc_(sizeof(SleeperRun));
    if (run != NULL)
    {
        run->duration = duration;
    }
    return (RunLoop){
        .tick = sleep_run_tick,
        .context = run,
        .manage_context = true,
    };
}

#endif // CSYNTH_SLEEP_RUN_H

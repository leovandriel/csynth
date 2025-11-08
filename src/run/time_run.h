#ifndef CSYNTH_TIME_RUN_H
#define CSYNTH_TIME_RUN_H

#include "../util/time.h"
#include "./run.h"

typedef struct
{
    double start;
    double duration;
} TimerRun;

csError time_run_init(void *context)
{
    TimerRun *run = (TimerRun *)context;
    run->start = time_sec();
    return csErrorNone;
}

csRunOrError time_run_tick(void *context)
{
    TimerRun *run = (TimerRun *)context;
    double time = time_sec();
    if (run->duration > 0 && time > run->start + run->duration)
    {
        return (csRunOrError){.run = csBreak};
    }
    return (csRunOrError){.run = csContinue};
}

RunLoop time_run(double duration)
{
    TimerRun *run = (TimerRun *)malloc_(sizeof(TimerRun));
    if (run != NULL)
    {
        run->duration = duration;
    }
    return (RunLoop){
        .init = time_run_init,
        .tick = time_run_tick,
        .context = run,
        .manage_context = true,
    };
}

#endif // CSYNTH_TIME_RUN_H

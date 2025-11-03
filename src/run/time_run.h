#ifndef CSYNTH_TIME_RUN_H
#define CSYNTH_TIME_RUN_H

#include "../util/time.h"
#include "./run.h"

typedef struct
{
    double start;
    double duration;
} TimerRun;

csError timer_run_init(void *context)
{
    TimerRun *run = (TimerRun *)context;
    if (run == NULL)
    {
        return error_type_message(csErrorMemoryAlloc, "Unable to allocate memory for timer run");
    }
    run->start = time_sec();
    return csErrorNone;
}

csError timer_run_tick(void *context)
{
    TimerRun *run = (TimerRun *)context;
    double time = time_sec();
    if (run->duration > 0 && time > run->start + run->duration)
    {
        return -1;
    }
    return csErrorNone;
}

void timer_run_free(void *context)
{
    free_(context);
}

RunLoop timer_run(double duration)
{
    TimerRun *run = (TimerRun *)malloc_(sizeof(TimerRun));
    if (run != NULL)
    {
        run->duration = duration;
    }
    return (RunLoop){
        .init = timer_run_init,
        .tick = timer_run_tick,
        .free = timer_run_free,
        .context = run,
    };
}

#endif // CSYNTH_TIME_RUN_H

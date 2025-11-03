#ifndef CSYNTH_TERMINAL_RUN_H
#define CSYNTH_TERMINAL_RUN_H

#include "../ui/terminal.h"
#include "../util/error.h"
#include "../util/time.h"
#include "./run.h"

typedef struct
{
    struct termios term;
    int exit_key;
} TerminalRun;

csError terminal_run_init(void *context)
{
    TerminalRun *run = (TerminalRun *)context;
    if (run == NULL)
    {
        return error_type_message(csErrorMemoryAlloc, "Unable to allocate memory for terminal run");
    }
    run->term = terminal_setup(1);
    signal(SIGINT, terminal_handler);
    return csErrorNone;
}

csError terminal_run_tick(void *context)
{
    TerminalRun *run = (TerminalRun *)context;
    if (terminal_signaled())
    {
        return -1;
    }
    int key = terminal_read(run->exit_key);
    if (key < 0)
    {
        return -1;
    }
    double time = time_sec();
    if (key > 0)
    {
        control_event_broadcast_keyboard(time, key);
    }
    return csErrorNone;
}

void terminal_run_free(void *context)
{
    TerminalRun *run = (TerminalRun *)context;
    terminal_restore(run->term);
    free_(run);
}

RunLoop terminal_run_with(int exit_key)
{
    TerminalRun *run = (TerminalRun *)malloc_(sizeof(TerminalRun));
    if (run != NULL)
    {
        run->exit_key = exit_key;
    }
    return (RunLoop){
        .init = terminal_run_init,
        .tick = terminal_run_tick,
        .free = terminal_run_free,
        .context = run,
    };
}

RunLoop terminal_run(void)
{
    return terminal_run_with(EXIT_KEY);
}

#endif // CSYNTH_TERMINAL_RUN_H

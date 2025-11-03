#ifndef CSYNTH_MIDI_RUN_H
#define CSYNTH_MIDI_RUN_H

#include "../ui/midi.h"
#include "./player_run.h"
#include "./sleep_run.h"
#include "./run.h"

#define MIDI_SLEEP_DURATION 0.001

typedef struct
{
    MidiContext context;
} MidiRun;


csError midi_run_init(void *context)
{
    MidiRun *run = (MidiRun *)context;
    if (run == NULL)
    {
        return error_type_message(csErrorMemoryAlloc, "Unable to allocate memory for midi run");
    }
    csError error = midi_initialize(&run->context);
    if (error != csErrorNone)
    {
        error_catch(error);
    }
    return csErrorNone;
}

csError midi_run_tick(void *context)
{
    MidiRun *run = (MidiRun *)context;
    return midi_read_broadcast(&run->context);
}

void midi_run_free(void *context)
{
    MidiRun *run = (MidiRun *)context;
    csError error = midi_terminate(&run->context);
    error_catch(error);
    free_(run);
}

RunLoop midi_run()
{
    MidiRun *run = (MidiRun *)malloc_(sizeof(MidiRun));
    return (RunLoop){
        .init = midi_run_init,
        .tick = midi_run_tick,
        .free = midi_run_free,
        .context = run,
    };
}

int play_midi(Func *input) { return run_loop(player_run(input), midi_run(), sleeper_run(MIDI_SLEEP_DURATION)); }
int play_midi_stereo(Func *left, Func *right) { return run_loop(player_run(left, right), midi_run(), sleeper_run(MIDI_SLEEP_DURATION)); }

#endif // CSYNTH_MIDI_RUN_H

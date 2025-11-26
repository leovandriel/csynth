#ifndef CSYNTH_MIDI_RUN_H
#define CSYNTH_MIDI_RUN_H

#include "../ui/midi.h"
#include "./player_run.h"
#include "./run.h"
#include "./sleep_run.h"

#define MIDI_SLEEP_DURATION 0.001

csError midi_run_init(void *context)
{
    return midi_init((MidiContext *)context);
}

csRunOrError midi_run_tick(void *context)
{
    return (csRunOrError)midi_read_broadcast((MidiContext *)context);
}

void midi_run_free(void *context)
{
    midi_free((MidiContext *)context);
}

RunLoop midi_run()
{
    return (RunLoop){
        .init = midi_run_init,
        .tick = midi_run_tick,
        .free = midi_run_free,
        .context = (MidiContext *)malloc_(sizeof(MidiContext)),
        .manage_context = true,
    };
}

csError play_midi(Func *input) { return run_loop(player_run(input), midi_run(), sleep_run(MIDI_SLEEP_DURATION)); }
csError play_midi_stereo(Func *left, Func *right) { return run_loop(player_run(left, right), midi_run(), sleep_run(MIDI_SLEEP_DURATION)); }

#endif // CSYNTH_MIDI_RUN_H

//usr/bin/gcc "$0" -o bin/times -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/times "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/midi_run.h"

int main(void)
{
    // press space to key note
    func note = pad(40, 9, decay_(.5, sine(C4)));
    return play_midi(note);
}

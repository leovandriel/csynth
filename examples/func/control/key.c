//usr/bin/gcc "$0" -o bin/key -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/key "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/midi_run.h"

int main(void)
{
    // press space to key note
    func note = key(50, 0, decay_(.5, sine(C4)));
    return play_midi(note);
}

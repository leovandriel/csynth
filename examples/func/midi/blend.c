//usr/bin/gcc "$0" -o bin/blend -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/blend "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/midi_player.h"

int main()
{
    // press space to key note
    func note = key(50, 0, decay_(.5, sine(C4)));
    return play_midi(note);
}

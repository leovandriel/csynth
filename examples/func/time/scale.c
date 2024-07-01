//usr/bin/gcc "$0" -o bin/scale -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/scale "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/midi_player.h"

int main()
{
    // press space to key note
    func note = pad(40, 9, decay_(.5, sine(C4)));
    return play_midi(note);
}

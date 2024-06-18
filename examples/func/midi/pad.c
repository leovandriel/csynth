//usr/bin/gcc "$0" -o bin/key -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/key "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/midi_player.h"

int main()
{
    // press space to key note
    func note = pad(40, 9, decay_(sine(C4), .5));
    return play_midi(mul_(note, .5));
}

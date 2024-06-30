//usr/bin/gcc "$0" -o bin/pad -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/pad "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/midi_player.h"

int main()
{
    // press space to key note
    func note = pad(40, 9, decay_(0.5, sine(C4)));
    return play_midi(mul_(0.5, note));
}

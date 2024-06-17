//usr/bin/gcc "$0" -o bin/key -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/key "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/midi_player.h"

int main()
{
    func tone = sine(knob_exp(70, C0, C9));
    return play_midi(mul_(tone, .5));
}
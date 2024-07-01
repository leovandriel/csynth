//usr/bin/gcc "$0" -o bin/knob -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/knob "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/midi_player.h"

int main()
{
    func tone = sine(knob_ex(70, 0, C0, C9));
    return play_midi(tone);
}

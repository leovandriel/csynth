//usr/bin/gcc "$0" -o bin/midi_value -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/midi_value "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/midi_run.h"

int main(void)
{
    func tone = sine(knob_ex(70, 0, C0, C9));
    return play_midi(tone);
}

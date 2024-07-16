//usr/bin/gcc "$0" -o bin/midi_keyboard -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/midi_keyboard "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/midi_player.h"

int main(void)
{
    func tone = sine(C0);
    func synth = midi_keyboard(1, tone);
    return play_midi(synth);
}

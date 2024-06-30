//usr/bin/gcc "$0" -o bin/midis -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/midis "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/midi_player.h"

int main()
{
    func note = unison_(5, 0.01, saw(C4));
    func keyboard = midi_keyboard(0, key, note);
    return play_midi(mul_(.5, keyboard));
}

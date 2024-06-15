//usr/bin/gcc "$0" -o bin/key -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/key "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/midi_player.h"

func note(func frequency)
{
    return unison(frequency, saw, 5, 0.01);
}

int main()
{
    func keyboard = midi_keyboard(0, key, note, C0);
    return play_midi(mul_(keyboard, .5));
}

//usr/bin/gcc "$0" -o bin/keyboard_synt -Wall -Wextra -O3 -lm -lportaudio && ./bin/keyboard_synth "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/player.h"
#include "../../src/ui/display.h"

func note(func frequency)
{
    return decay_(unison(frequency, saw, 5, 0.01), 0.5);
}

int main()
{
    func drums = add(
        trigger('q', bdrum()),
        trigger('w', snare()),
        trigger('e', hihat()));
    func keys = mul_(keyboard(trigger, note, C4), .5);
    return play(add(drums, keys));
}

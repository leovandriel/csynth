//usr/bin/gcc "$0" -o bin/keyboard_synth -Wall -Wextra -O3 -lm -lportaudio && ./bin/keyboard_synth "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/player.h"
#include "../../src/ui/display.h"

int main(void)
{
    func drums = add(
        trigger('q', bdrum()),
        trigger('w', snare()),
        trigger('e', hihat()));
    func note = decay_(.5, unison_(5, .01, saw(C4)));
    func keys = mul_(.5, keyboard(trigger, note));
    return play(add(drums, keys));
}

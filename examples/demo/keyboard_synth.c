//usr/bin/true && ./utils/run.c "$0" -Wall -Wextra -O3 -lm -lportaudio; exit $?
#include "../../src/func/all.h"
#include "../../src/io/term_player.h"
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

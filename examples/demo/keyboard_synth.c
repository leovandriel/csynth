//usr/bin/gcc "$0" -o bin/keyboard_synth -Wall -Wextra -O3 -lm -lportaudio && ./bin/keyboard_synth "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/run/play.h"
#include "../../src/run/terminal_run.h"

int main(void)
{
    func drums = mul_(2, add(
                             trigger('q', bdrum()),
                             trigger('w', snare()),
                             trigger('e', hihat())));
    func note = decay_(.5, unison_(5, .01, saw(C4)));
    func keys = mul_(.5, keyboard(trigger, note));
    return play(add(drums, keys), terminal_run());
}

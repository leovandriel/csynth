//usr/bin/true && ./utils/run.c "$0" -Wall -Wextra -O3 -lm -lportaudio; exit $?
// Based on: https://supercollider.github.io/examples
#include "../../src/func/all.h"
#include "../../src/io/term_player.h"

int main(void)
{
    func snare = loop_(1, delay_(.5, decay_(.05, white())));
    func bdrum = loop_(1, mul_(3, decay_(.05, sine(linear_env_(1, 60, 30)))));
    func hihat = loop_(.25, decay_(.05, hpf_(20000, white())));
    func drummer = mul_(.4, add(snare, bdrum, hihat));
    return play(drummer);
}

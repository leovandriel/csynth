//usr/bin/gcc "$0" -o bin/drummer -Wall -Wextra -O3 -lm -lportaudio && ./bin/drummer "$@"; exit $?
// Based on: https://supercollider.github.io/examples
#include "../../src/func/all.h"
#include "../../src/io/player.h"

int main()
{
    func snare = loop_(1, delay_(.5, decay_(.05, uniform())));
    func bdrum = loop_(1, mul(decay_(.05, sine(linear_env_(1, 60, 30))), _(3)));
    func hihat = loop_(.25, decay_(.05, hpf_(20000, uniform())));
    func drummer = mul_(.4, add(snare, bdrum, hihat));
    return play(drummer);
}

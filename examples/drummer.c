//usr/bin/gcc "$0" -o bin/drummer -Wall -Wextra -O3 -lm -lportaudio && ./bin/drummer "$@"; exit $?
// Based on: https://supercollider.github.io/examples
#include "../src/func/all.h"
#include "../src/io/player.h"

int main()
{
    func snare = loop_(delay_(mul(uniform(), decay_(.05)), .5), 1);
    func bdrum = loop_(mul(sine(linear_(60, 30, 1)), decay_(.05), _(3)), 1);
    func hihat = loop_(mul(high_pass_(uniform(), 20000), decay_(.05)), .25);
    func drummer =  mul_(add(snare, bdrum, hihat), .4);
    return play(drummer);
}

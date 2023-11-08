// Based on: https://supercollider.github.io/examples
#include "../func/all.h"

func drummer()
{
    func snare = loop_(delay_(mul(noise(), decay_(.05)), .5), 1);
    func bdrum = loop_(mul(sine(linear_(60, 30, 1)), decay_(.05), _(3)), 1);
    func hihat = loop_(mul(high_pass_(noise(), 20000), decay_(.05)), .25);
    return mul_(add(snare, bdrum, hihat), .4);
}
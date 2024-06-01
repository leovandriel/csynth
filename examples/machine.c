//usr/bin/gcc "$0" -o bin/machine -Wall -Wextra -O3 -lm -lportaudio && ./bin/machine "$@"; exit $?
#include "../src/func/all.h"
#include "../src/io/player.h"

int main()
{
    func snare = mul(uniform(), decay_(.05));
    func bdrum = mul(sine(linear(C1, C0, ONE)), decay_(.4), _(3));
    func hihat = mul(high_pass_(uniform(), 20000), decay_(.05));
    func patterns = add(
        pattern_("................", hihat, .25, .001),
        pattern_("  .   .   .   . ", snare, .25, .001),
        pattern_(".    .  .    .  ", bdrum, .25, .001));
    func machine = mul_(loop_(patterns, 4), .4);
    return play(machine);
}

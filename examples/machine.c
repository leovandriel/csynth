//usr/bin/gcc "$0" -o bin/machine -Wall -Wextra -O3 -lm -lportaudio && ./bin/machine "$@"; exit $?
#include "../src/func/all.h"
#include "../src/util/player.h"

int main()
{
    func snare = mul(noise(), decay_(.05));
    func bdrum = mul(sine(linear_(60, 30, 1)), decay_(.05), _(3));
    func hihat = mul(high_pass_(noise(), 20000), decay_(.05));
    func patterns = add(
        pattern_("  .   .   .   . ", snare, .25),
        pattern_(".    .  .    .  ", bdrum, .25),
        pattern_("................", hihat, .25));
    func machine = mul_(loop_(patterns, 4), .4);
    return play(machine, 8);
}

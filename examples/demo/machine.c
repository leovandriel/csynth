//usr/bin/gcc "$0" -o bin/machine -Wall -Wextra -O3 -lm -lportaudio && ./bin/machine "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/player.h"

int main()
{
    func snare = decay_(uniform(), .05);
    func bdrum = mul(decay_(sine(linear_env(C1, C0, ONE)), .4), _(3));
    func hihat = decay_(hpf_(uniform(), 20000), .05);
    func triggers = add(
        trigger('q', hihat),
        trigger('w', snare),
        trigger('e', bdrum));
    func patterns = add(
        pattern_("................", actuate('q'), .25, .001),
        pattern_("  .   .   .   . ", actuate('w'), .25, .001),
        pattern_(".    .  .    .  ", actuate('e'), .25, .001));
    func machine = add(triggers, loop_(patterns, 4));
    return play(mul_(machine, .4));
}

//usr/bin/gcc "$0" -o bin/machine -Wall -Wextra -O3 -lm -lportaudio && ./bin/machine "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/player.h"

int main()
{
    func triggers = add(
        trigger('q', hihat()),
        trigger('w', snare()),
        trigger('e', bdrum()));
    func patterns = add(
        pattern_("................", actuate('q'), .25, .001),
        pattern_("  .   .   .   . ", actuate('w'), .25, .001),
        pattern_(".    .  .    .  ", actuate('e'), .25, .001));
    func machine = add(triggers, loop_(patterns, 4));
    return play(mul_(machine, .4));
}

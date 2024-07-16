//usr/bin/gcc "$0" -o bin/machine -Wall -Wextra -O3 -lm -lportaudio && ./bin/machine "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/player.h"

int main(void)
{
    func triggers = add(
        trigger('q', hihat()),
        trigger('w', snare()),
        trigger('e', bdrum()));
    func patterns = add(
        pattern_("................", .25, .001, actuate('q')),
        pattern_("  .   .   .   . ", .25, .001, actuate('w')),
        pattern_(".    .  .    .  ", .25, .001, actuate('e')));
    func machine = add(triggers, loop_(4, patterns));
    return play(machine);
}

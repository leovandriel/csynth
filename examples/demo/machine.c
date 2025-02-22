//usr/bin/true && ./utils/run.c "$0" -Wall -Wextra -O3 -lm -lportaudio; exit $?
#include "../../src/func/all.h"
#include "../../src/io/term_player.h"

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

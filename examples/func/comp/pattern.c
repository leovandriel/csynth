//usr/bin/gcc "$0" -o bin/pattern -Wall -Wextra -O3 -lm -lportaudio && ./bin/pattern "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main(void)
{
    func patterns = add(
        pattern_("................", .25, .01, hihat()),
        pattern_("  .   .   .   . ", .25, .01, snare()),
        pattern_(".    .  .    .  ", .25, .01, bdrum()));
    return play(loop_(4, patterns));
}

//usr/bin/gcc "$0" -o bin/pattern -Wall -Wextra -O3 -lm -lportaudio && ./bin/pattern "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/play.h"

func note(func frequency)
{
    return mul_(.5, decay_(.2, unison_(4, .01, saw(frequency))));
}

func arp(func note1, func note2, func note3)
{
    return add(
        pattern_(".  .  . ", .25, .01, note(note1)),
        pattern_(" .  .   ", .25, .01, note(note2)),
        pattern_("  .  . .", .25, .01, note(note3)));
}

int main(void)
{
    func comp = add(
        pattern_(".   .   ", 2, .01, arp(F4, A4, C5)),
        pattern_(" .   .  ", 2, .01, arp(G4, B4, D5)),
        pattern_("  .   . ", 2, .01, arp(E4, G4, B4)),
        pattern_("   .   .", 2, .01, arp(F4, A4, C6)));
    return play(tempo_(1.5, comp));
}

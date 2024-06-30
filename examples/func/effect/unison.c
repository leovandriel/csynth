//usr/bin/gcc "$0" -o bin/unison -Wall -Wextra -O3 -lm -lportaudio && ./bin/unison "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // unison saw wave keyboard, with 10 voices and 1% detune
    func note = decay_(0.5, unison_(10, 0.01, saw(C4)));
    func fun = keyboard(trigger, note);
    return play(mul_(.5, fun));
}

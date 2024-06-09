//usr/bin/gcc "$0" -o bin/unison -Wall -Wextra -O3 -lm -lportaudio && ./bin/unison "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

Func *note(Func *frequency)
{
    return decay_(unison(frequency, saw, 10, 0.01), 0.5);
}

int main()
{
    // unison saw wave keyboard, with 10 voices and 1% detune
    func fun = keyboard(trigger, note, C4);
    return play(mul_(fun, .5));
}

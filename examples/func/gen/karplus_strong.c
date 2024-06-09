//usr/bin/gcc "$0" -o bin/karplus_strong -Wall -Wextra -O3 -lm -lportaudio && ./bin/karplus_strong "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

Func *note(Func *frequency)
{
    return karplus_strong(frequency, const_(.3));
}

int main()
{
    // strings keyboard
    func fun = (keyboard(trigger, note, C4));
    printf("keyboard keys: %s\n", keyboard_keys);
    return play(mul_(fun, .5));
}

//usr/bin/gcc "$0" -o bin/karplus_strong -Wall -Wextra -O3 -lm -lportaudio && ./bin/karplus_strong "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // strings keyboard
    func note = karplus_strong_(C4, .3);
    func fun = keyboard(trigger, note);
    printf("keyboard keys: %s\n", keyboard_keys);
    return play(fun);
}

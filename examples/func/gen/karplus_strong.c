//usr/bin/gcc "$0" -o bin/karplus_strong -Wall -Wextra -O3 -lm -lportaudio && ./bin/karplus_strong "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // strings keyboard
    func note = karplus_strong_(C4, .3);
    func fun = keyboard(trigger, note);
    log_info("keyboard keys: %s", KEYBOARD_KEYS);
    return play(fun);
}

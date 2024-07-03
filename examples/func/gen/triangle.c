//usr/bin/gcc "$0" -o bin/triangle -Wall -Wextra -O3 -lm -lportaudio && ./bin/triangle "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // triangle wave keyboard
    func fun = keyboard(unmute, mul_(.5, triangle(C4)));
    log_info("keyboard keys: %s", KEYBOARD_KEYS);
    return play(fun);
}

//usr/bin/gcc "$0" -o bin/square -Wall -Wextra -O3 -lm -lportaudio && ./bin/square "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/term_player.h"

int main(void)
{
    // square wave keyboard
    func fun = keyboard(unmute, mul_(.2, square(C4)));
    log_info("keyboard keys: %s", KEYBOARD_KEYS);
    return play(fun);
}

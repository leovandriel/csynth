//usr/bin/gcc "$0" -o bin/saw -Wall -Wextra -O3 -lm -lportaudio && ./bin/saw "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/term_player.h"

int main(void)
{
    // sawtooth wave keyboard
    func fun = keyboard(unmute, mul_(.3, saw(C4)));
    log_info("keyboard keys: %s", KEYBOARD_KEYS);
    return play(fun);
}

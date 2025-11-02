//usr/bin/gcc "$0" -o bin/sine -Wall -Wextra -O3 -lm -lportaudio && ./bin/sine "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/play.h"

int main(void)
{
    // sine wave keyboard
    func fun = keyboard(unmute, sine(C4));
    log_info("keyboard keys: %s", KEYBOARD_KEYS);
    return play(fun);
}

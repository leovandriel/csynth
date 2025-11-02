//usr/bin/gcc "$0" -o bin/overtone -Wall -Wextra -O3 -lm -lportaudio && ./bin/overtone "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/play.h"

int main(void)
{
    // TODO(leo): implement
    func fun = keyboard(unmute, mul_(.3, saw(C4)));
    log_info("keyboard keys: %s", KEYBOARD_KEYS);
    return play(fun);
}

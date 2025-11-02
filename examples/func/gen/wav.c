//usr/bin/gcc "$0" -o bin/wav -Wall -Wextra -O3 -lm -lportaudio && ./bin/wav "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/play.h"

int main(void)
{
    // play meow keyboard
    func note = keyboard(trigger, wav("examples/meow.wav"));
    log_info("keyboard keys: %s", KEYBOARD_KEYS);
    return play(note);
}

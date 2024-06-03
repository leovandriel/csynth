//usr/bin/gcc "$0" -o bin/square -Wall -Wextra -O3 -lm -lportaudio && ./bin/square "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // square wave keyboard
    func f = (keyboard(unmute, square, C4));
    printf("keyboard keys: %s\n", keyboard_keys);
    return play(mul_(f, .1));
}

//usr/bin/gcc "$0" -o bin/sine -Wall -Wextra -O3 -lm -lportaudio && ./bin/sine "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // sine wave keyboard
    func fun = (keyboard(unmute, sine, C4));
    printf("keyboard keys: %s\n", keyboard_keys);
    return play(mul_(fun, .2));
}

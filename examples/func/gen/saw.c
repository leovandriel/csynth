//usr/bin/gcc "$0" -o bin/saw -Wall -Wextra -O3 -lm -lportaudio && ./bin/saw "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // sawtooth wave keyboard
    func fun = keyboard(unmute, mul_(.3, saw(C4)));
    printf("keyboard keys: %s\n", keyboard_keys);
    return play(fun);
}

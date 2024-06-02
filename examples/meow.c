//usr/bin/gcc "$0" -o bin/meow -Wall -Wextra -O3 -lm -lportaudio && ./bin/meow "$@"; exit $?
#include "../src/func/all.h"
#include "../src/io/player.h"

func meow(func factor)
{
    return wav_filename("output/meow.wav", 0, factor);
}

int main()
{
    printf("keyboard keys: %s\n", keyboard_keys);
    play(mul_(keyboard_(trigger, meow, 1), 0.4));
}

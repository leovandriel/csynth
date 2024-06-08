//usr/bin/gcc "$0" -o bin/tutorial -Wall -Wextra -O3 -lm -lportaudio && ./bin/tutorial "$@"; exit $?
#include "../src/func/all.h"
#include "../src/io/player.h"

int main()
{
    return play(sine(A4));
}

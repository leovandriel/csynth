//usr/bin/gcc "$0" -o bin/crack -Wall -Wextra -O3 -lm -lportaudio && ./bin/crack "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    return play(mul_(crack_(0.001), .5));
}

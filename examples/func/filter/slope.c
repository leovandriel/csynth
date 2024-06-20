//usr/bin/gcc "$0" -o bin/slope -Wall -Wextra -O3 -lm -lportaudio && ./bin/slope "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // square wave filtered with decreasing limit on slope
    func tone = square(A4);
    func sloped = slope(tone, expo(linear_env_(10, 0, 10)));
    return play(mul_(sloped, .2));
}

//usr/bin/gcc "$0" -o bin/gauss -Wall -Wextra -O3 -lm -lportaudio && ./bin/gauss "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // gaussian noise, normal distributed amplitude
    func fun = gauss();
    return play(mul_(fun, .2));
}

//usr/bin/gcc "$0" -o bin/gens -Wall -Wextra -O3 -lm -lportaudio && ./bin/gens "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // ONE and ZERO are shortcuts for const_(1) and const_(0)
    func fun = crack(ONE);
    return play(fun);
}

//usr/bin/gcc "$0" -o bin/gens -Wall -Wextra -O3 -lm -lportaudio && ./bin/gens "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/term_player.h"

int main(void)
{
    // ONE and ZERO are shorthand for const_(1) and const_(0)
    func fun = crack(ONE);
    return play(fun);
}

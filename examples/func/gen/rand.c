//usr/bin/gcc "$0" -o bin/rand -Wall -Wextra -O3 -lm -lportaudio && ./bin/uniform "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/term_player.h"

int main(void)
{
    // white noise
    func fun = mul_(.5, white());
    return play(fun);
}

//usr/bin/gcc "$0" -o bin/pink -Wall -Wextra -O3 -lm -lportaudio && ./bin/pink "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main(void)
{
    // pink noise
    func fun = mul_(.5, pink());
    return play(fun);
}

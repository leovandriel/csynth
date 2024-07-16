//usr/bin/gcc "$0" -o bin/tanh -Wall -Wextra -O3 -lm -lportaudio && ./bin/tanh "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main(void)
{
    // tanh distortion
    func note = tanh_op(sine(C4));
    return play(note);
}

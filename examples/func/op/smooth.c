//usr/bin/gcc "$0" -o bin/smooth -Wall -Wextra -O3 -lm -lportaudio && ./bin/smooth "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main(void)
{
    // Fade in using smooth step
    func note = smooth_(0.1, 0.9, sine(C4));
    return play(note);
}

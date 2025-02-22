//usr/bin/gcc "$0" -o bin/tutorial -Wall -Wextra -O3 -lm -lportaudio && ./bin/tutorial "$@"; exit $?
#include "../src/func/all.h"
#include "../src/io/term_player.h"

int main(void)
{
    func tone = sine(A4);
    return play(tone);
}

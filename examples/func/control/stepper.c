//usr/bin/gcc "$0" -o bin/stepper -Wall -Wextra -O3 -lm -lportaudio && ./bin/stepper "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/term_player.h"

int main(void)
{
    // press space, followed by up/down to change frequency wit 10 HZ
    func note = sine(stepper(' ', C4_, 10));
    return play(note);
}

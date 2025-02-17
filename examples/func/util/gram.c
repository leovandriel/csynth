//usr/bin/gcc "$0" -o bin/gram -Wall -Wextra -O3 -lm -lportaudio && ./bin/gram "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main(void)
{
    func note = gram(sine(C4));
    return play(note);
}

//usr/bin/gcc "$0" -o bin/gamma -Wall -Wextra -O3 -lm -lportaudio && ./bin/gamma "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/term_player.h"

int main(void)
{
    // Gamma shape
    func note = gamma_(triangle(C4), 2);
    return play(note);
}

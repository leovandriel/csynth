//usr/bin/gcc "$0" -o bin/mul -Wall -Wextra -O3 -lm -lportaudio && ./bin/mul "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // Multiply two notes
    func note = add(sine(C4), sine(E4));
    return play(note);
}

//usr/bin/gcc "$0" -o bin/neg -Wall -Wextra -O3 -lm -lportaudio && ./bin/neg "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/play.h"

int main(void)
{
    // Negated note
    func note = neg(sine(C4));
    return play(note);
}

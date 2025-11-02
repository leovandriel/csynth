//usr/bin/gcc "$0" -o bin/continuous -Wall -Wextra -O3 -lm -lportaudio && ./bin/continuous "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/play.h"

int main(void)
{
    // TODO(leo): Implement
    func note = hush(sine(C4));
    return play(note);
}

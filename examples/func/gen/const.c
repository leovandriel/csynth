//usr/bin/gcc "$0" -o bin/const -Wall -Wextra -O3 -lm -lportaudio && ./bin/const "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/play.h"

int main(void)
{
    // play a constant frequency, same as sine(_(440)) or simply sine_(440)
    func note = sine(const_(440));
    return play(note);
}

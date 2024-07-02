//usr/bin/gcc "$0" -o bin/gauge -Wall -Wextra -O3 -lm -lportaudio && ./bin/gauge "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    func note = sine(C4);
    return play(fps("funcs per sample", note));
}

//usr/bin/gcc "$0" -o bin/fps -Wall -Wextra -O3 -lm -lportaudio && ./bin/fps "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/play.h"

int main(void)
{
    func note = sine(C4);
    return play(fps("funcs per sample", note));
}

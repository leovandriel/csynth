//usr/bin/true && ./utils/run.c "$0" -Wall -Wextra -O3 -lm -lportaudio; exit $?
#include "../src/func/all.h"
#include "../src/io/player.h"

int main(void)
{
    func tone = sine(A4);
    return play(tone);
}

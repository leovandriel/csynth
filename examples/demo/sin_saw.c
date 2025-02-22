//usr/bin/true && ./utils/run.c "$0" -Wall -Wextra -O3 -lm -lportaudio; exit $?
#include "../../src/func/all.h"
#include "../../src/io/term_player.h"

int main(void)
{
    func high = sine(A4);
    func low = mul_(.5, saw(A2));
    func beep = rect_(0, .1, high);
    func boop1 = rect_(.4, .5, low);
    func boop2 = rect_(1, 1.1, low);
    func melody = add(beep, boop1, boop2);
    func looped = loop_(1.6, melody);
    func echoed = reverb_(.2, .5, looped);
    func scaled = mul_(.1, echoed);
    return play(scaled);
}

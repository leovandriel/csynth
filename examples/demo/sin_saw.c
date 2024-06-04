//usr/bin/gcc "$0" -o bin/sin_saw -Wall -Wextra -O3 -lm -lportaudio && ./bin/sin_saw "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/player.h"

int main()
{
    func high = sine(A4);
    func low = mul_(saw(A2), .5);
    func beep = block_(high, 0, .1);
    func boop1 = block_(low, .4, .5);
    func boop2 = block_(low, 1, 1.1);
    func melody = add(beep, boop1, boop2);
    func looped = loop_(melody, 1.6);
    func echoed = reverb_(looped, .2, .5);
    func scaled = mul_(echoed, .1);
    return play(scaled);
}

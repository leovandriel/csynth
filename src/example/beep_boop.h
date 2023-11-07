#include "../func/all.h"

func beep_boop()
{
    func high = sine(A4);
    func low = mul_(saw(A2), .5);
    func beep = mul(high, block_(0, .1));
    func boop1 = mul(low, block_(.4, .5));
    func boop2 = mul(low, block_(1, 1.1));
    func melody = add(beep, boop1, boop2);
    func looped = loop_(melody, 1.6);
    func echoed = reverb_(looped, .2, .5);
    func scaled = mul_(echoed, .1);
    return scaled;
}

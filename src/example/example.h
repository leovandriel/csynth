#include "../func/all.h"

func example()
{
    func tone = sine(A4);
    func note = mul(tone, block_(0, .3), _(.5));
    func looped = loop_(note, 1.5);
    func revved = reverb_(looped, .4, .2);
    return revved;
}

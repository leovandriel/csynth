#include "../func/all.h"

#define P(_f) (mul(_f, pitch))
#define T(_f) (dvd(_(_f), speed))

static func beep_boop_dynamic(func pitch, func speed)
{
    func high = sine(P(A4));
    func low = mul_(saw(P(A2)), .5);
    func beep = mul(high, block(T(0), T(.1)));
    func boop1 = mul(low, block(T(.4), T(.5)));
    func boop2 = mul(low, block(T(1), T(1.1)));
    func melody = add(beep, boop1, boop2);
    func looped = loop(melody, T(1.6));
    func echoed = reverb(looped, T(.2), _(.5));
    func scaled = mul_(echoed, .1);
    return scaled;
}

func wobble_both()
{
    func wobble = continuous(add_(mul_(sine_(.1), .1), 1));
    return beep_boop_dynamic(wobble, wobble);
}

func modulate_pitch()
{
    func modulate = continuous(add_(mul_(timer(), .5), .01));
    return beep_boop_dynamic(modulate, ONE);
}

func modulate_speed()
{
    func modulate = continuous(add_(mul_(timer(), .5), .01));
    return beep_boop_dynamic(ONE, modulate);
}

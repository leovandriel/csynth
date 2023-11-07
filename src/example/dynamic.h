#include "../core/funcs.h"

static func g_pitch = NULL;
static func g_speed = NULL;

static func P(func f)
{
    return mul(f, g_pitch);
}

static func T(double f)
{
    return dvd(_(f), g_speed);
}

static func beep_boop_dynamic(func pitch, func speed)
{
    g_pitch = pitch;
    g_speed = speed;
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

func increase_pitch()
{
    func increase = continuous(add_(mul_(timer(), .5), .01));
    return beep_boop_dynamic(increase, ONE);
}

func increase_speed()
{
    func increase = continuous(add_(mul_(timer(), .5), .01));
    return beep_boop_dynamic(ONE, increase);
}

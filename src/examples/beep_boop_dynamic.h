#include "../core/funcs.h"

static func g_pitch = NULL;
static func g_speed = NULL;

func P(func f)
{
    return mul(f, g_pitch);
}

func T(double f)
{
    return mul(_(f), inv(g_speed));
}

func beep_boop_dynamic(func pitch, func speed)
{
    g_pitch = pitch;
    g_speed = speed;
    func high = sine(P(A4));
    func low = mul(saw(P(A2)), _(.5));
    func beep = mul(high, block(T(0), T(.1)));
    func boop1 = mul(low, block(T(.4), T(.5)));
    func boop2 = mul(low, block(T(1), T(1.1)));
    func melody = add(beep, boop1, boop2);
    func looped = loop(melody, T(1.6));
    func echoed = reverb(looped, T(.2), _(.5));
    func scaled = mul(echoed, _(.1));
    return scaled;
}

func beep_boop_slow()
{
    return beep_boop_dynamic(_(.5), _(.5));
}

func beep_boop_fast()
{
    return beep_boop_dynamic(_(2), _(2));
}

// TODO: fix the reverb buffer resize

func beep_boop_wobble()
{
    func wobble = add(mul(sine(_(1)), _(.1)), _(1));
    return beep_boop_dynamic(wobble, wobble);
}

func beep_boop_increase()
{
    func increase = add(mul(timer(), _(.2)), _(.5));
    return beep_boop_dynamic(increase, increase);
}

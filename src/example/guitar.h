#include "../core/funcs.h"

func strum(const func *c, int count, double span, double decay)
{
    func notes[10];
    for (int i = 0; i < count; i++)
    {
        func f = karplus_strong(c[i], _(decay));
        f = low_pass(f, c[i]);
        f = delay_(f, span * (span < 0 ? i - count : i));
        notes[i] = f;
    }
    return add_array(count, notes);
}

func pluck(func _frequency)
{
    func f = add_(div_(sine(div_(_frequency, 4)), 100), 1);
    f = mul(_frequency, f);
    f = karplus_strong(f, _(.5));
    f = low_pass(f, _frequency);
    return f;
}

#define slow(_chord) (strum((func[]){_chord}, sizeof((func[]){_chord}) / sizeof(func), .1, .3))
#define down(_chord) (strum((func[]){_chord}, sizeof((func[]){_chord}) / sizeof(func), .01, .5))
#define up(_chord) (strum((func[]){_chord}, sizeof((func[]){_chord}) / sizeof(func), -.01, .5))

#define Dm A2, D3, A3, D3, F4
#define F C3, F3, A3, C4
#define G G2, B2, D3, G3, B3, G4
#define Am A2, E3, A3, C4, E4

func t(int index)
{
    return _(0.25 * index + (0.01 * rand() / RAND_MAX));
}

func guitar()
{
    func g0 = comp_abs(
        t(0), slow(Am),
        t(8), slow(Am));

    func g1 = comp_abs(
        t(0), pluck(D5),
        t(1), pluck(E5),
        t(2), pluck(D5),
        t(3), pluck(A4));

    func guitar1 = comp_abs(
        t(0), g1,
        t(16), g1,
        t(32), g1,
        t(48), g1);

    func g2 = comp_abs(
        t(0), down(F),
        t(3), up(F),
        t(4), down(F),
        t(5), up(F),
        t(7), up(F),
        t(9), up(Dm),
        t(11), up(Dm),
        t(12), down(G),
        t(14), down(G));

    func g3 = comp_abs(
        t(0), down(Am),
        t(3), up(Am),
        t(4), down(Am),
        t(5), up(Am),
        t(7), up(Am),
        t(9), up(Am),
        t(11), up(Am),
        t(12), down(G),
        t(13), down(G),
        t(14), down(G),
        t(15), down(G));

    func guitar2 = comp_abs(
        t(4), g2,
        t(20), g3,
        t(36), g2,
        t(52), g3);

    return comp_abs(
        t(0), g0,
        t(18), add(guitar1, guitar2));
}

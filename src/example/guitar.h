#include "../func/all.h"

static func strum(int count, const double *c, double span, double decay)
{
    func notes[10];
    for (int i = 0; i < count; i++)
    {
        func f = karplus_strong_(c[i], decay);
        f = low_pass_(f, c[i]);
        f = delay_(f, span * (span < 0 ? i - count : i));
        notes[i] = f;
    }
    return add_array(count, notes);
}

static func pluck(func frequency)
{
    func f = karplus_strong(frequency, _(.6));
    f = clamp_(mul_(f, 10), -1, 1);
    f = low_pass(f, dvd_(frequency, 2));
    return f;
}

#define slow(_chord) (strum(sizeof(_chord) / sizeof(func), _chord, .1, .3))
#define down(_chord) (strum(sizeof(_chord) / sizeof(func), _chord, .01, .5))
#define up(_chord) (strum(sizeof(_chord) / sizeof(func), _chord, -.01, .5))

static const double Dm[] = {A2_, D3_, A3_, D3_, F4_};
static const double F[] = {C3_, F3_, A3_, C4_};
static const double G[] = {G2_, B2_, D3_, G3_, B3_, G4_};
static const double Am[] = {A2_, E3_, A3_, C4_, E4_};

static func t(int index)
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

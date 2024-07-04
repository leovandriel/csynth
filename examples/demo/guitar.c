//usr/bin/gcc "$0" -o bin/guitar -Wall -Wextra -O3 -lm -lportaudio && ./bin/guitar "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/player.h"

static func strum(int count, const double *freqs, double span, double decay)
{
    func notes[10];
    for (int i = 0; i < count; i++)
    {
        func note = karplus_strong_(_(freqs[i]), decay);
        note = lpf_(freqs[i], note);
        note = delay_(span * (double)(span < 0 ? i - count : i), note);
        notes[i] = note;
    }
    return add_create(count, notes);
}

static func pluck(func frequency)
{
    func note = karplus_strong_(frequency, .6);
    note = clamp_(-1, 1, mul_(10, note));
    note = lpf(dvd_(frequency, 2), note);
    return note;
}

#define slow(_chord) (strum(sizeof(_chord) / sizeof(func), _chord, .1, .3))
#define down(_chord) (strum(sizeof(_chord) / sizeof(func), _chord, .01, .5))
#define up(_chord) (strum(sizeof(_chord) / sizeof(func), _chord, -.01, .5))

static const double Dm_[] = {A2_, D3_, A3_, D3_, F4_};
static const double F__[] = {C3_, F3_, A3_, C4_};
static const double G__[] = {G2_, B2_, D3_, G3_, B3_, G4_};
static const double Am_[] = {A2_, E3_, A3_, C4_, E4_};

static func t(double index)
{
    return _(.25 * index + rand_range(0, .01));
}

int main()
{
    func gg0 = seq_abs(
        t(0), slow(Am_),
        t(8), slow(Am_));

    func gg1 = seq_abs(
        t(0), pluck(D5),
        t(1), pluck(E5),
        t(2), pluck(D5),
        t(3), smooth_inv(t(1), t(1.5), pluck(A4)));

    func guitar1 = seq_abs(
        t(0), gg1,
        t(16), gg1,
        t(32), gg1,
        t(48), gg1);

    func gg2 = seq_abs(
        t(0), down(F__),
        t(3), up(F__),
        t(4), down(F__),
        t(5), up(F__),
        t(7), up(F__),
        t(9), up(Dm_),
        t(11), up(Dm_),
        t(12), down(G__),
        t(14), down(G__));

    func gg3 = seq_abs(
        t(0), down(Am_),
        t(3), up(Am_),
        t(4), down(Am_),
        t(5), up(Am_),
        t(7), up(Am_),
        t(9), up(Am_),
        t(11), up(Am_),
        t(12), down(G__),
        t(13), down(G__),
        t(14), down(G__),
        t(15), down(G__));

    func guitar2 = seq_abs(
        t(4), gg2,
        t(20), gg3,
        t(36), gg2,
        t(52), gg3);

    func guitar = seq_abs(
        t(0), gg0,
        t(18), add(guitar1, guitar2));
    return play_duration(24, guitar);
}

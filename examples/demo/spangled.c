//usr/bin/gcc "$0" -o bin/spangled -Wall -Wextra -O3 -lm -lportaudio && ./bin/spangled "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/player.h"

double speed = 0.4;

static func A(func frequency, double duration)
{
    double delta = speed * duration;
    func note = saw(frequency);
    note = chorus_(note, sine_(.2), 0.02, 0.003);
    note = lpf(note, A2);
    note = adsr_(note, delta / 4, delta / 8, 0.8, delta / 8, delta);
    return note;
}

static func B(func frequency, double duration)
{
    double delta = speed * duration;
    func note = add(
        mul_(sine(mul_(frequency, 2)), 0.2),
        mul_(sine(dvd_(frequency, 2)), 0.2));
    note = rect_(note, 0, delta);
    return add(note, A(frequency, duration));
}

static func C(func frequency, double duration)
{
    double delta = speed * duration;
    func note = karplus_strong(frequency, _(0.8));
    note = lpf(note, frequency);
    note = rect_(note, 0, delta);
    note = distort_(note, 30);
    note = mul_(note, 0.05);
    return add(note, A(frequency, duration));
}

int main()
{
    func ff1 = seq_seq(
        A(G4, 1.5),
        A(E4, .5),
        A(C4, 2),
        A(E4, 2),
        A(G4, 2),
        A(C5, 4),
        A(E5, 1.5),
        A(D5, .5),
        A(C5, 2),
        A(E4, 2),
        A(Fs4, 2),
        A(G4, 4),
        A(G4, 1),
        A(G4, 1),
        A(E5, 3),
        A(D5, 1),
        A(C5, 2),
        A(B4, 4),
        A(A4, 1),
        A(B4, 1),
        A(C5, 2),
        A(C5, 2),
        A(G4, 2),
        A(E4, 2),
        A(C4, 2));

    func ff2 = seq_seq(
        B(G4, 1.5),
        B(E4, .5),
        B(C4, 2),
        B(E4, 2),
        B(G4, 2),
        B(C5, 4),
        B(E5, 1.5),
        B(D5, .5),
        B(C5, 2),
        B(E4, 2),
        B(Fs4, 2),
        B(G4, 4),
        B(G4, 1),
        B(G4, 1),
        B(E5, 3),
        B(D5, 1),
        B(C5, 2),
        B(B4, 4),
        B(A4, 1),
        B(B4, 1),
        B(C5, 2),
        B(C5, 2),
        B(G4, 2),
        B(E4, 2),
        B(C4, 2));

    func ff3 = seq_seq(
        C(E5, 1),
        C(E5, 1),
        C(E5, 2),
        C(F5, 2),
        C(G5, 2),
        C(G5, 4),
        C(F5, 1),
        C(E5, 1),
        C(D5, 2),
        C(E5, 2),
        C(F5, 2),
        C(F5, 4),
        C(F5, 2),
        C(E5, 3),
        C(D5, 1),
        C(C5, 2),
        C(B4, 4),
        C(A4, 1.5),
        C(B4, .5),
        C(C5, 2),
        C(E4, 2),
        C(Fs4, 2),
        C(G4, 4),
        C(G4, 2),
        C(C5, 2),
        C(C5, 2),
        C(C5, 1),
        C(B4, 1),
        C(A4, 2),
        C(A4, 2),
        C(A4, 2),
        C(D5, 2),
        C(F5, 1),
        C(E5, 1),
        C(D5, 1),
        C(C5, 1),
        C(C5, 2),
        C(B4, 2),
        C(G4, 1),
        C(G4, 1),
        C(C5, 3),
        C(D5, 1),
        C(E5, 1),
        C(F5, 1),
        C(G5, 4),
        C(C5, 1),
        C(D5, 1),
        C(E5, 3),
        C(F5, 1),
        C(D5, 2),
        C(C5, 4));
    func sequence = seq_rel(ff1, _(48.5 * speed), ff2, _(48.5 * speed), ff3, _(98 * speed));
    func spangled = reverb_(sequence, 0.1, 0.5);
    return play_(spangled, 80);
}

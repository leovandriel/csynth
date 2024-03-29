#include "../func/all.h"

double speed = 0.4;

static func A(func frequency, double duration)
{
    double d = speed * duration;
    func f = saw(frequency);
    f = chorus_(f, sine_(.2), 0.02, 0.003);
    f = low_pass(f, A2);
    f = mul(f, adsr_(d / 4, d / 8, 0.8, d / 8, d));
    return f;
}

static func B(func frequency, double duration)
{
    double d = speed * duration;
    func f = add(
        mul(sine(mul_(frequency, 2)), _(0.2)),
        mul(sine(dvd_(frequency, 2)), _(0.2)));
    f = mul(f, block_(0, d));
    return add(f, A(frequency, duration));
}

double tanh_distort(double x, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    return fmin(fmax(tanh(x * 10), -0.3), 0.3);
}

static func C(func frequency, double duration)
{
    double d = speed * duration;
    func f = karplus_strong(frequency, _(0.8));
    f = low_pass(f, frequency);
    f = mul(f, block_(0, d));
    f = callback_filter(f, tanh_distort, NULL);
    f = mul_(f, 0.1);
    return add(f, A(frequency, duration));
}

func spangled()
{
    func f1 = comp_seq(
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

    func f2 = comp_seq(
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

    func f3 = comp_seq(
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
    func f = comp_rel(f1, _(48.5 * speed), f2, _(48.5 * speed), f3, _(98 * speed));
    f = reverb_(f, 0.1, 0.5);
    return f;
}

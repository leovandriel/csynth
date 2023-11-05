#include "./core/funcs.h"
#include "./core/writer.h"

func beep_boop()
{
    func high = sine(A3);
    func low = mul(saw(A1), _(.5));
    func beep = mul(high, block(0, .1));
    func boop1 = mul(low, block(.4, .5));
    func boop2 = mul(low, block(1, 1.1));
    func melody = sum(beep, boop1, boop2);
    func looped = loop(melody, _(1.6));
    func echoed = reverb(looped, _(.2), _(.5));
    func scaled = mul(echoed, _(.1));
    return scaled;
}

func shapes()
{
    func all = comp(
        mul(sine(A4), _(.5)), _(0.3), ZERO, _(0.2),
        mul(triangle(A4), _(.5)), _(0.3), ZERO, _(0.2),
        mul(square(A4), _(.25)), _(0.3), ZERO, _(0.2),
        mul(saw(A4), _(.25)), _(0.3), ZERO, _(0.2));
    func looped = loop(all, _(2));
    func scaled = mul(looped, _(.1));
    return scaled;
}

func beats()
{
    func base = mul(sine(A1), hump(0, 0.01, .05, .1), _(2));
    func hat = mul(sum(saw(A5), noise()), hump(0, 0.005, 0.005, .01), _(.5));
    func base_line = comp(
        base, _(1.25), base, _(.75),
        base, _(1.25), base, _(.5), base, _(.25),
        base, _(1.25), base, _(.75),
        base, _(1.25), base, _(.5), base, _(.12), base, _(.13));
    func hat_line = comp(
        ZERO, _(.5), hat, _(1), hat, _(.5),
        ZERO, _(.5), hat, _(1), hat, _(.5),
        ZERO, _(.5), hat, _(1), hat, _(.25), hat, _(.12), hat, _(.13),
        ZERO, _(.5), hat, _(1), hat, _(.5));
    func low_line = comp(
        mul(sine(A0), hump(0, 0.05, 1.95, 2), _(8)), _(2),
        mul(sine(E1), hump(0, 0.05, .7, .75), _(8)), _(.75),
        mul(sine(D1), hump(0, 0.05, .7, .75), _(8)), _(.75),
        mul(sine(E1), hump(0, 0.05, .45, .5), _(8)), _(.5),
        mul(sine(A1), hump(0, 0.05, 1.95, 2), _(8)), _(2),
        mul(sine(C1), hump(0, 0.05, 1.95, 2), _(8)), _(2));
    func composition = sum(base_line, hat_line, low_line);
    func looped = loop(composition, _(8));
    func scaled = mul(looped, _(.1));
    return scaled;
}

func filters()
{
    func input = noise();
    func each = _(1);
    int count = 8;
    func lows = comp(
        lowpass(input, mul(A0, _(.0625))), each,
        lowpass(input, mul(A0, _(.125))), each,
        lowpass(input, mul(A0, _(.25))), each,
        lowpass(input, mul(A0, _(.5))), each,
        lowpass(input, A0), each,
        lowpass(input, A1), each,
        lowpass(input, A2), each,
        lowpass(input, A3), each);
    func highs = comp(
        highpass(input, mul(A10, _(16))), each,
        highpass(input, mul(A10, _(8))), each,
        highpass(input, mul(A10, _(4))), each,
        highpass(input, mul(A10, _(2))), each,
        highpass(input, A10), each,
        highpass(input, A9), each,
        highpass(input, A8), each,
        highpass(input, A7), each);
    func composition = comp(
        mul(sine(A3), _(.25)), _(1), lows, mul(each, _(count)),
        mul(sine(A3), _(.25)), _(1), highs, mul(each, _(count)));
    func looped = loop(composition, _(2 * count + 2));
    func scaled = mul(looped, _(.1));
    return scaled;
}

func lows()
{
    Func *notes[] = {Fs4, E4, D4, Cs4, B3, A3, B3, Cs4};
    Func *inputs[80];
    for (int i = 0; i < 40; i++)
    {
        Func *note = notes[i % 8];
        Func *tone = sine(mul(note, _(pow(0.5, i / 8))));
        double gain = i < 32 ? 1 << (i / 8) : 10;
        inputs[i * 2] = mul(tone, _(gain), hump(0, .1, .9, 1));
        inputs[i * 2 + 1] = _(1);
    }
    func composition = comp_rel_array(80, inputs);
    func looped = loop(composition, _(40));
    func scaled = mul(looped, _(.1));
    return scaled;
}

int main(void)
{
    write(beep_boop(), 8);
    // write(beats(), 16);
    // write(shapes(), 15);
    // write(filters(), 30);
    // write(lows(), 30);
    return 0;
}

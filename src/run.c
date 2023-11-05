#include "./core/funcs.h"
#include "./core/writer.h"

func beep_boop()
{
    func high = sine(A3);
    func low = mul(saw(A1), cons(.5));
    func beep = mul(high, block(0, .1));
    func boop1 = mul(low, block(.4, .5));
    func boop2 = mul(low, block(1, 1.1));
    func melody = sum(beep, boop1, boop2);
    func looped = loop(melody, cons(1.6));
    func echoed = reverb(looped, cons(.2), cons(.5));
    func scaled = mul(echoed, cons(.1));
    return scaled;
}

func shapes()
{
    func all = comp(
        mul(sine(A4), cons(.5)), cons(0.3), ZERO, cons(0.2),
        mul(triangle(A4), cons(.5)), cons(0.3), ZERO, cons(0.2),
        mul(square(A4), cons(.25)), cons(0.3), ZERO, cons(0.2),
        mul(saw(A4), cons(.25)), cons(0.3), ZERO, cons(0.2));
    func looped = loop(all, cons(2));
    func scaled = mul(looped, cons(.1));
    return scaled;
}

func beats()
{
    func base = mul(sine(A1), hump(0, 0.01, .05, .1), cons(2));
    func hat = mul(sum(saw(A5), noise()), hump(0, 0.005, 0.005, .01), cons(.5));
    func base_line = comp(
        base, cons(1.25), base, cons(.75),
        base, cons(1.25), base, cons(.5), base, cons(.25),
        base, cons(1.25), base, cons(.75),
        base, cons(1.25), base, cons(.5), base, cons(.12), base, cons(.13));
    func hat_line = comp(
        ZERO, cons(.5), hat, cons(1), hat, cons(.5),
        ZERO, cons(.5), hat, cons(1), hat, cons(.5),
        ZERO, cons(.5), hat, cons(1), hat, cons(.25), hat, cons(.12), hat, cons(.13),
        ZERO, cons(.5), hat, cons(1), hat, cons(.5));
    func low_line = comp(
        mul(sine(A0), hump(0, 0.05, 1.95, 2), cons(8)), cons(2),
        mul(sine(E1), hump(0, 0.05, .7, .75), cons(8)), cons(.75),
        mul(sine(D1), hump(0, 0.05, .7, .75), cons(8)), cons(.75),
        mul(sine(E1), hump(0, 0.05, .45, .5), cons(8)), cons(.5),
        mul(sine(A1), hump(0, 0.05, 1.95, 2), cons(8)), cons(2),
        mul(sine(C1), hump(0, 0.05, 1.95, 2), cons(8)), cons(2));
    func composition = sum(base_line, hat_line, low_line);
    func looped = loop(composition, cons(8));
    func scaled = mul(looped, cons(.1));
    return scaled;
}

func filters()
{
    func input = noise();
    func each = cons(1);
    int count = 8;
    func lows = comp(
        lowpass(input, mul(A0, cons(.0625))), each,
        lowpass(input, mul(A0, cons(.125))), each,
        lowpass(input, mul(A0, cons(.25))), each,
        lowpass(input, mul(A0, cons(.5))), each,
        lowpass(input, A0), each,
        lowpass(input, A1), each,
        lowpass(input, A2), each,
        lowpass(input, A3), each);
    func highs = comp(
        highpass(input, mul(A10, cons(16))), each,
        highpass(input, mul(A10, cons(8))), each,
        highpass(input, mul(A10, cons(4))), each,
        highpass(input, mul(A10, cons(2))), each,
        highpass(input, A10), each,
        highpass(input, A9), each,
        highpass(input, A8), each,
        highpass(input, A7), each);
    func composition = comp(
        // sine(A3), cons(1), noise(), cons(1),
        mul(sine(A3), cons(.25)), cons(1), lows, mul(each, cons(count)),
        // sine(A3), cons(1), noise(), cons(1),
        mul(sine(A3), cons(.25)), cons(1), highs, mul(each, cons(count)));
    func looped = loop(composition, cons(2 * count + 2));
    func scaled = mul(looped, cons(.1));
    return scaled;
}

func lows()
{
    Func *notes[] = {Fs4, E4, D4, Cs4, B3, A3, B3, Cs4};
    Func *inputs[80];
    for (int i = 0; i < 40; i++)
    {
        Func *note = notes[i % 8];
        Func *tone = sine(mul(note, cons(pow(0.5, i / 8))));
        double gain = i < 32 ? 1 << (i / 8) : 10;
        inputs[i * 2] = mul(tone, cons(gain), hump(0, .1, .9, 1));
        inputs[i * 2 + 1] = cons(1);
    }
    func composition = comp_rel_array(80, inputs);
    func looped = loop(composition, cons(40));
    func scaled = mul(looped, cons(.1));
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

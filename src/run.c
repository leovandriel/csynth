#include "./core/funcs.h"
#include "./core/writer.h"

func beep_boop()
{
    func high = sine(A4);
    func low1 = mul(saw(A2), cons(.5));
    func low2 = mul(saw(A2), cons(.5));
    func beep = mul(high, block(0, .1));
    func boop1 = mul(low1, block(.4, .5));
    func boop2 = mul(low2, block(1, 1.1));
    func melody = sum_3(beep, boop1, boop2);
    func looped = loop(melody, cons(1.6));
    func echoed = reverb(looped, cons(.2), cons(.5));
    func scaled = mul(echoed, cons(.1));
    return scaled;
}

func shapes()
{
    func all = comp(17,
                    mul(sine(A5), cons(.5)), cons(0.3), ZERO, cons(0.2),
                    mul(triangle(A5), cons(.5)), cons(0.3), ZERO, cons(0.2),
                    mul(square(A5), cons(.25)), cons(0.3), ZERO, cons(0.2),
                    mul(saw(A5), cons(.25)), cons(0.3), ZERO, cons(0.2),
                    ZERO);
    func looped = loop(all, cons(2));
    func scaled = mul(looped, cons(.1));
    return scaled;
}

func beats()
{
    func base = mul_3(sine(A2), hump(0, 0.01, .05, .1), cons(2));
    func hat = mul_3(sum(saw(A6), noise()), hump(0, 0.005, 0.005, .01), cons(.5));
    func base_line = comp(22,
                          base, cons(1.25), base, cons(.75),
                          base, cons(1.25), base, cons(.5), base, cons(.25),
                          base, cons(1.25), base, cons(.75),
                          base, cons(1.25), base, cons(.5), base, cons(.12), base, cons(.13),
                          ZERO);
    func hat_line = comp(28,
                         ZERO, cons(.5), hat, cons(1), hat, cons(.5),
                         ZERO, cons(.5), hat, cons(1), hat, cons(.5),
                         ZERO, cons(.5), hat, cons(1), hat, cons(.25), hat, cons(.12), hat, cons(.13),
                         ZERO, cons(.5), hat, cons(1), hat, cons(.5),
                         ZERO);
    func low_line = comp(12,
                         mul_3(sine(A1), hump(0, 0.05, 1.95, 2), cons(8)), cons(2),
                         mul_3(sine(E1), hump(0, 0.05, .7, .75), cons(8)), cons(.75),
                         mul_3(sine(D1), hump(0, 0.05, .7, .75), cons(8)), cons(.75),
                         mul_3(sine(E1), hump(0, 0.05, .45, .5), cons(8)), cons(.5),
                         mul_3(sine(A2), hump(0, 0.05, 1.95, 2), cons(8)), cons(2),
                         mul_3(sine(C1), hump(0, 0.05, 1.95, 2), cons(8)), cons(2),
                         ZERO);
    func composition = sum_3(base_line, hat_line, low_line);
    func looped = loop(composition, cons(8));
    func scaled = mul(looped, cons(.1));
    return scaled;
}

func filters()
{
    func input = noise();
    func each = cons(1);
    int count = 8;
    func lows = comp(2 * count,
                     lowpass(input, mul(A0, cons(.25))), each,
                     lowpass(input, mul(A0, cons(.5))), each,
                     lowpass(input, A0), each,
                     lowpass(input, A1), each,
                     lowpass(input, A2), each,
                     lowpass(input, A3), each,
                     lowpass(input, A4), each,
                     lowpass(input, A5), each,
                     ZERO);
    func highs = comp(2 * count,
                      highpass(input, mul(A10, cons(16))), each,
                      highpass(input, mul(A10, cons(8))), each,
                      highpass(input, mul(A10, cons(4))), each,
                      highpass(input, mul(A10, cons(2))), each,
                      highpass(input, A10), each,
                      highpass(input, A9), each,
                      highpass(input, A8), each,
                      highpass(input, A7), each,
                      ZERO);
    func composition = comp(8,
                            // sine(A4), cons(1), noise(), cons(1),
                            mul(sine(A4), cons(.25)), cons(1), lows, mul(each, cons(count)),
                            // sine(A4), cons(1), noise(), cons(1),
                            mul(sine(A4), cons(.25)), cons(1), highs, mul(each, cons(count)),
                            ZERO);
    func looped = loop(composition, cons(2 * count + 2));
    func scaled = mul(looped, cons(.1));
    return scaled;
}

func lows()
{
    Func *notes[] = {Fs4, E4, D4, Cs4, B4, A4, B4, Cs4};
    Func *inputs[80];
    for (int i = 0; i < 40; i++)
    {
        Func *note = notes[i % 8];
        Func *tone = sine(mul(note, cons(pow(0.5, i / 8))));
        double gain = i < 32 ? 1 << (i / 8) : 10;
        inputs[i * 2] = mul_3(tone, cons(gain), hump(0, .1, .9, 1));
        inputs[i * 2 + 1] = cons(1);
    }
    func composition = comp_args(80, inputs);
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

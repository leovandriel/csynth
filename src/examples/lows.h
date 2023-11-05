#include "../core/funcs.h"

func lows()
{
    Func *notes[] = {Fs4, E4, D4, Cs4, B3, A3, B3, Cs4};
    Func *inputs[80];
    for (int i = 0; i < 40; i++)
    {
        Func *note = notes[i % 8];
        Func *tone = sine(mul(note, _(pow(0.5, i / 8))));
        double gain = i < 32 ? 1 << (i / 8) : 10;
        inputs[i * 2] = mul(tone, _(gain), hump_(0, .1, .9, 1));
        inputs[i * 2 + 1] = _(1);
    }
    func composition = comp_rel_array(80, inputs);
    func looped = loop(composition, _(40));
    func scaled = mul(looped, _(.1));
    return scaled;
}

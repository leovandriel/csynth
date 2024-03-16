//usr/bin/gcc "$0" -o bin/play -Wall -Wextra -O3 -lm -lportaudio && ./bin/play "$@"; exit $?
#include "./src/util/player.h"
#include "./src/func/all.h"

typedef enum
{
    SINE,
    SAW,
    GUITAR,
    WEWEW
} Instrument;

const double gain = .5;
const double start = 250;
const double increment = 1.1;
const Instrument instrument = WEWEW;

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
    Func *inputs[40];
    char buffer[100];
    double length = 0, frequency = start;
    for (int i = 0; i < 40; i++)
    {
        func tone;
        switch (instrument)
        {
        case SINE:
            tone = sine_(frequency);
            break;
        case SAW:
            tone = saw_(frequency);
            break;
        case GUITAR:
            tone = karplus_strong_(frequency, .6);
            break;
        case WEWEW:
            tone = sine(mul(_(frequency), add(mul(sine_(5), _(.1)), _(.9))));
            break;
        }
        func beep = mul(tone, _(gain), hump_(0, .1, .9, 1));
        sprintf(buffer, "frequency: %.2f", frequency);
        inputs[i] = print(buffer, beep);
        frequency = round(frequency * increment / 10) * 10;
        length += 1;
    }
    func composition = comp_seq_array(40, inputs);
    func looped = loop_(composition, 40);
    func scaled = mul_(looped, .1);
    play(scaled, length);
    return 0;
}
